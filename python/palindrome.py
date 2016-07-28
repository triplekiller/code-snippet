#!/usr/bin/env python3

class ShortInputException(Exception):
    '''A user-defined exception class.'''

    def __init__(self, length, atleast):
        Exception.__init__(self)
        self.length = length
        self.atleast = atleast

def reverse(text):
    return text[::-1]

def is_palindrome(text):
    return text == reverse(text)

input_str = input("Enter text: ")
if is_palindrome(input_str):
    print("Yes")
else:
    print("No")

# Acquiring a resource in the try block and subsequently releasing
# the resource in the finally block is a common pattern.

try:
    text_input = input("Enter something ---> ")
    if len(text_input) < 3:
        raise ShortInputException(len(text_input), 3)
except EOFError:
    print("\nWhy did you do an EOF on me?")
except KeyboardInterrupt:
    print("\nYou cancelled the operation.")
except ShortInputException as ex:
    print("\nShortInputException: input len is {0}, expected len is {1}".format
            (ex.length, ex.atleast))
else:
    print("\nYou entered {}".format(text_input))
