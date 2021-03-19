# CS50-projects

Here is an archive of my CS50 projects.
The first 5 weeks of CS50 are primarily in C, so I learned my fundamentals of coding and algorithms in C.
This evolved into higher level programming like Python and Javascript as well as markup languages like HTML/CSS for web development.
My web programming experience was primarily with Flask framrwork.

In certain C programs, a library caled cs50.h is included. This training-wheel library was intended to help us get off our feet when starting programming, as to focus on the more important concepts, such as algorithm logic or learning the syntax of a language.

I've included my first week's projects (for reference later in life), as well as a few programs from weeks 2 onwards that I enjoyed or are diverse enough to warrant uploading it.

## Week 1 projects:  
**Hello.c:** Obligatory hello world, my first program written in C.  
**Cash.c:** This simple command-line program asks user for an amount of money and outputs the minimum number of coins needed to get that cash in all coins.  
**Credit.c:** This program tests if a credit card number is valid or not using the appropriate algorithms. While these early codes are very dirty and unefficient, I think looking back on where I start will be very important to keep improving and revisiting old programs in order to improve them as fun exercises in the future.  
**Mario.c:** A simple command-line program that takes an integer (1 - 8) as input and outputs a mario-style pyramid of blocks as hash (#) symbols.  
**Population.c:** User inputs a starting population and an end (target) population. At certain pre-determined birth and death rates, the program will output the number of years needed to reach the target population.  

## Other projects:  
**Volume.c:** This command-line program takes a .wav file as a command line argument and is able to control the volume output of the file. Using the file structure of .wav files, we parse the .wav file in a 44 byte chunk to find the .wav header. After, the program parses through the rest of the file in 44 byte chunks and adjusts the volume for each byte, effectively modifying the volume of the total file. The correct way to write the command is as follows (input.wav is the input file, output.wav is the name of the file after being changed, factor is the multiplying factor to be applied to the volume, which can take float point values such as 0.5 to half the volume): $ ./volume input.was output.wav factor  
**Readability.c:** This command-line program takes as input a text (from a word to multiple sentences) and determines the estimated grade level of that text. It takes into consideration the number of syllables per word, the number of words per sentences and a few more values to estimate the number. It can estimate from "before grade 1" up to "grade 16+", where 16+ indicates at least 4 years of post-secondary education).  
**Readability.py:** This python program was a few weeks after starting CS50, where we revisited our old C programs to re-write them in python and appreciate the difference between low-level languages and high-level languages. This experiment was very fun and it's most likely at this point where I realized the amount of knowledge we acquired since starting CS50.
**Fiftyville:** This wonderful SQL (sqlite3) challenge was one of the funnest assignments we had to complete. A murder-mystery style database of people, interview records, camera records, car license plates, telephone records, etc. was given to us in a .db file. Using SQL queries, we had to collect information and cross-reference the "clues" we discovered as we went on. The only hint we were given to start was "The crime took place on July 28, 2020 and it took place on Chamberlin Street". This was an increddibly creative way to test our SQL query skills and I thoroughly enjoyed this assignment.  
