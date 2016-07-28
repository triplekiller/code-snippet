#!/usr/bin/python

nums = range(2, 100)
for i in range(2, 8):
    nums = filter(lambda x: x == i or x % i, nums)

print nums

print map(lambda w: len(w), "It's raining cats and dogs".split())

def foo(bar):
    bar = 'new value'
    print('{} in foo'.format(bar))

def foo2(bar):
    bar.append(42)
    print('{} in foo2'.format(bar))

# binding names to object
# call-by-object-reference
answer_list = 'old value' # string is immutable
foo(answer_list)
print(answer_list)

answer_list_2 = [] # list is mutable
foo2(answer_list_2)
print(answer_list_2)
