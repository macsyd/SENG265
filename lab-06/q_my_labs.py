#!/usr/bin/env python3

import datetime

def main():
    """
    Create a datetime object for today's date
    """

    # COMPLETE IMPLEMENTATION
    todays_date = datetime.date.today()

    date_list = every_lab(todays_date)

    """ 
    variable date_list should contain datetime objects 
    for all the days when you have a lab
    print these dates in the format "Mon, 21 November 22"
    """

    # COMPLETE IMPLEMENTATION
    for each in date_list:
        print(each.strftime("%a"), " ", each.strftime("%d"), " ", each.strftime("%B"), " ", each.strftime("%y"))


def every_lab(todays_date):
    """
    Classes for the current semester end on Dec 6 2022.

    Assume that you have a lab every week till the end of classes. 
    (Only your lab, in this instance.)

    This function will create datetimes objects for those labs, 
    add them to a list and then return this list
    """
    labs = []
    diff = datetime.timedelta(days = 7)
    next_date = todays_date + diff
    while(next_date < datetime.date(2022, 12, 6)):
        labs.append(next_date)
        next_date += diff
    return labs

if __name__ == "__main__":
    main()
