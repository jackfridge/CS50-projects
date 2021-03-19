import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime
import time
import string

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# $ export API_KEY=pk_b1ddb043873348fda43096062e3f8553
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # only GET method enabled, so no method if statement required for post vs get
    # generate list of unique stock symbols for current user
    rows = db.execute("SELECT symbol FROM shares WHERE user_id=? GROUP BY symbol", session.get("user_id"))

    portfolio = []

    for row in rows:
        name = row["symbol"]

        # for each unique symbol, generate sum of shares, associated to the symbol in the dict (share is the key)
        shares = db.execute("SELECT SUM(share_qty) FROM shares WHERE user_id=? AND symbol=? GROUP BY symbol HAVING SUM(share_qty) >= 1",
            session.get("user_id"), row["symbol"])

        # remove any symbol that has a sum of 0 from the list
        if shares == []:
            continue

        # calculate current value of the stock
        price = lookup(row["symbol"])

        name = {
            "symbol": row["symbol"].upper(),
            "shares": shares[0]["SUM(share_qty)"],
            "price": usd(price["price"]),
            "value": float(round(shares[0]["SUM(share_qty)"] * price["price"], 2))
        }

        # add dictionary to list (keep all dicts for number of unique stocks)
        portfolio.append(name)

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session.get("user_id"))

    # round cash to 2 decimals
    cash = cash[0]["cash"]

    # sum of all amounts for total account value
    total = float(cash)
    cash = usd(cash)

    for x in range(len(portfolio)):
        total += portfolio[x]["value"]
        portfolio[x]["value"] = usd(portfolio[x]["value"])

    total = usd(total)

    # pass rows so all stocks with prices can be passed to the index page
    return render_template("index.html", rows=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if isinstance(request.form.get("shares"), int):
            if request.form.get("shares") <= 0:
                return apology("Invalid number of shares", 400)

        if isinstance(request.form.get("shares"), float):
            return apology("Invalid number of shares", 400)

        if request.form.get("shares").isalpha():
            return apology("Invalid number of shares", 400)

        if request.form.get("shares").isdecimal() == False:
            return apology("Invalid number of shares", 400)

        # make sure symbol requested is valid (similar to the quote.html page)
        if lookup(request.form.get("symbol")) != None:

            # store symbol, shares input and price of stock asked
            symbol = request.form.get("symbol")
            shares = int(request.form.get("shares"))
            price = lookup(request.form.get("symbol"))
            price = float(price["price"])

            # obtain total value to subtract value from user's cash
            total = float(price * shares)

            row = db.execute("SELECT * FROM users WHERE id=?", session.get("user_id"))

            if len(row) != 1:
                return apology("unexpected error")

            else:
                current_cash = float(row[0]["cash"])

            # for valid amount (not passing current cash), buy shares and store data in new table (shares)
            if total < current_cash:

                # update new cash after purchase
                current_cash -= total
                current_time = datetime.now()

                # update cash value in SQL
                db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session.get("user_id"))

                # add stock shares in second SQL
                db.execute("INSERT INTO shares(user_id, symbol, share_qty, buy_price, buy_date) VALUES(?, ?, ?, ?, ?)",
                    session.get("user_id"), symbol, shares, price, current_time)

                return redirect("/")

            else:
                return apology("You do not have enough cash to complete this purchase")

        else:
            return apology("invalid symbol")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # only GET method, so retrieve all data from user id's stock activity
    rows = db.execute("SELECT symbol, share_qty, buy_price, buy_date FROM shares WHERE user_id = ? ORDER BY buy_date",
        session.get("user_id"))

    for row in rows:
        row["symbol"] = row["symbol"].upper()
        row["buy_price"] = usd(row["buy_price"])

    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if (lookup(request.form.get("symbol"))) != None:

            # quote variable is the value of the lookup function if it returns a value
            quote = lookup(request.form.get("symbol"))
            price = quote["price"]
            price = usd(price)

            # Passing the quote to the html to display the value correctly
            return render_template("quoted.html", quote=quote, price=price)

        else:
            return apology("invalid stock symbol")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    #TODO: create registration page (include SQL queries in finance.db, calling db.execute())
    # For POST method of the form, go through registration procedure to attempt adding a new user
    if request.method == "POST":

        # Make sure a username was typed
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Make sure a password was typed and confirmation
        elif not request.form.get("password") or not request.form.get("password"):
            return apology("must provide password and confirmation", 400)

        # Password confirmation must match password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password must match", 400)

        # Check if there is any row in the database with the username typed
        rows = db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))

        # Must return = results for a valid username, if anything else, it's already taken
        if not rows:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"),
                generate_password_hash(request.form.get("password")))

        # If registration successful, hash password in database and return login page
        else:
            return apology("this username has already been taken", 400)

        return redirect("/login")

    # If it's a GET request, nothing was posted and show the registration page
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # When user posts request to sell
    if request.method == "POST":
        # check if stock symbol is valid or not
        if lookup(request.form.get("symbol")) != None:
            symbol = request.form.get("symbol")
            sell_shares = request.form.get("shares")

            # check if user owns that stock
            owns = db.execute("SELECT * FROM shares WHERE symbol=?", request.form.get("symbol"))

            # if no stock of the input symbol is owned, invalid sell
            if owns != []:
                # check if user owns enough shares of that stock
                own_shares = db.execute("SELECT SUM(share_qty) FROM shares WHERE user_id=? AND symbol=?",
                    session.get("user_id"), request.form.get("symbol"))

                own_shares = own_shares[0]["SUM(share_qty)"]
                sell_shares = int(sell_shares)

                if own_shares >= sell_shares:
                    # determine current value of stock
                    price = lookup(symbol)
                    price = price["price"]
                    value = price * sell_shares

                    current_time = datetime.now()

                    # subtract shares, convert to cash
                    db.execute("INSERT INTO shares(user_id, symbol, share_qty, buy_price, buy_date) VALUES(?, ?, ?, ?, ?)",
                        session.get("user_id"), symbol, -sell_shares, -price, current_time)

                    current_cash = db.execute("SELECT cash FROM users WHERE id = ?", session.get("user_id"))
                    current_cash = current_cash[0]["cash"]

                    current_cash += value

                    db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session.get("user_id"))

                    return redirect("/")

                else:
                    return apology("you do not own enough of that stock to sell")

            else:
                return apology("you do not own this stock")

            # if stock # is zero, remove that row from SQL

        else:
            return apology("invalid symbol")

    else:
        return render_template("sell.html")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    """Add cash to user's account"""
    if request.method == "POST":
        cash = float(request.form.get("cash"))

        # get current cash
        current_cash = db.execute("SELECT cash FROM users WHERE id=?", session.get("user_id"))

        # add cash to existing cash for user
        current_cash = current_cash[0]["cash"] + cash

        # update cash in SQL to reflect newly added cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session.get("user_id"))

        return redirect("/")

    else:
        return render_template("cash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
