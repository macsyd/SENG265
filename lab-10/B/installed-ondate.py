#!/usr/bin/env python3

import re
import sys

def main():
    if len(sys.argv) < 2:
        sys.exit(0)

    date = sys.argv[1];
    line_number = 0

    pattern = re.compile(r"(\d{4}-\d{2}-\d{2}) (.+) installed ((.+):(.+)) .*")

    for line in sys.stdin:
        line = line.rstrip()
        line_number += 1
        
        m = pattern.search(line)
        if m:
            if(m.group(1) == date):
                print("%s: %s" % (m.group(1), m.group(4)))

if __name__ == "__main__":
    main()
