#!/usr/bin/python3

# This is a guess the number game.
import random
secret_number = random.randint(1, 20)
print("I am thinking of a number between 1 and 20 (inclusive).")

# Ask the player to guess 6 times.
for guesses_taken in range(1, 7):
    guess = int(input("Take a guess. "))
    if guess < secret_number:
        print("Your guess is too low.")
    elif guess > secret_number:
        print("Your guess is too high.")
    else:
        break # correct guess!

if guess == secret_number:
    if guesses_taken > 1:
        print("Good job! You guessed my number in " + str(guesses_taken)
                + " guesses!")
    else:
        print("Good job! You guessed my number in 1 guess!")
else:
    print("Nope. The number I was thinking of was " + str(secret_number))
