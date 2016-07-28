#!/usr/bin/env python3

# Decorator: function wrappers that are run when the python interpreter loads
# the function, and can modify what the function receives and returns.

from time import sleep
from functools import wraps
import logging

logging.basicConfig()
log = logging.getLogger("retry")

def retry(f):
    @wraps(f)
    def wrapped_f(*args, **kwargs):
        MAX_ATTEMPTS = 5
        for attempt in range(1, MAX_ATTEMPTS + 1):
            try:
                return f(*args, **kwargs)
            except:
                log.exception("Attempt %s/%s failed: %s", attempt, MAX_ATTEMPTS,
                        (args, kwargs))
                sleep(10 * attempt)

        log.critical("All %s attempts failed: %s", MAX_ATTEMPTS, (args, kwargs))

    return wrapped_f

counter = 0

@retry
def save_to_db(arg):
    print("Write to database.")
    print("Automatically retried if exception is thrown.")
    global counter
    counter += 1

    if counter < 2:
        raise ValueError(arg)

if __name__ == '__main__':
    save_to_db("Some bad value")
