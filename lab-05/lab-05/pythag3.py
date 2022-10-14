#!/usr/bin/env python3

import sys

def pythag(a, b):
    return (a ** 2 + b ** 2)**(1/2)

def main():
 
    # parse the command-line arguments
    # print an error and quit if there aren't the right number
    if(len(sys.argv) != 3):
        print("Run with two arguments")
    
    # convert the command line arguments from strings to floats
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    

    print("Sides ", a, " and ", b, ", hypotenuse ", end="", sep="")
    print("%.4f" % pythag(a, b))


if __name__ == "__main__":
    main()
