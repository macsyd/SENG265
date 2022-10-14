#!/usr/bin/env python3

import sys

def main():

    # Write your code here.  Refer to the hints provided
    # in the lab PDF.
    if(len(sys.argv) < 2):
        print("Input a string")
        exit()
    
    s = sys.argv[1]
    lines = s.split(',')
    for a in lines:
        print(a)

if __name__ == "__main__":
    main()
