#!/usr/bin/env python3

# usage: ./gen-message.py <csv-file-name>
import re
import datetime
import fileinput


template = """SUBSCRIPTION EXPIRY MESSAGE

=FIRSTNAME= =LASTNAME=
=TODAY=


Dear =FIRSTNAME=:

Our records show that your subscription to "Unix Users Quarterly"
expired on =EXPIRATION=.

If you would like to keep your subscription active, we request
payment by =PAYDATE=.

Yours sincerely,

Uriah Heep
"""

dirpath = "messages/"


def main():
    today = datetime.date.today()
    six_weeks_from_today = today + datetime.timedelta(weeks=6)

    today = today.strftime("%B %d %Y")
    six_weeks_from_today = six_weeks_from_today.strftime("%B %d %Y")

    for line in fileinput.input():
        line = line.rstrip()
        (lastname, firstname, expire, code) = line.split(",")

        message = re.sub("=FIRSTNAME=", firstname, template)
        message = re.sub("=LASTNAME=", lastname, message)
        message = re.sub("=EXPIRATION=", expire, message)
        message = re.sub("=PAYDATE=", six_weeks_from_today, message)
        message = re.sub("=TODAY=", today, message)
        
        f = open(dirpath + code + ".txt", "w")
        f.write(message)
        f.close()

if __name__ == "__main__":
    main()
