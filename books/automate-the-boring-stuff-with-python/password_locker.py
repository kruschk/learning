#!/usr/bin/python3

# password_locker.py: an insecure password locker program

PASSWORDS = {
        "email": "abcd1234",
        "blog": "password",
        "luggage": "12345"
}

import sys, pyperclip

if len(sys.argv) < 2:
    print("Usage: python3 " + sys.argv[0] + " account")
    sys.exit()

account = sys.argv[1] # first command line arg is the account name

if account in PASSWORDS:
    pyperclip.copy(PASSWORDS[account])
    print("Password for " + account + " copied to clipboard.")
else:
    print("There is no account named " + account)
