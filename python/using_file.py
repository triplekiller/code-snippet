#!/usr/bin/env python3

poem = '''\
Programming is fun
When the work is done
If you wanna make your work also fun:
    use Python!
'''

f = open('poem.txt', 'w')
f.write(poem)
f.close()

with open("poem.txt") as f:
    for line in f:
        print(line, end='')

f = open('poem.txt')
while True:
    line = f.readline()
    if len(line) == 0:
        break
    print(line, end='')

f.close()
