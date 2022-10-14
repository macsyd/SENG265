#! /usr/bin/env python3

import sys

def main():
    
    #  Read the words from sys.stdin
    #  Keep only the unique words
    #  Print them in sorted order.
    lst = []
    for line in sys.stdin:
        new_line = line.split('\n')
        words = new_line[0].split(',')
        for each in words:
            lst.append(each)
    
    lst = set(lst)
    lst = list(lst)
    lst.sort()
    for word in lst:
        print(word)

if __name__ == "__main__":
    main()
