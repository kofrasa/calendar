/*
 * File:   calendar.c
 * Author: Francis Asante
 *
 * Created on November 7, 2009, 10:48 PM
 */

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include "calendar.h"

const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int monthCodes[12] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

void help() {
    printf("Displays a calendar for years between 1900 and 2099.\n\n");
    printf("./calendar [yyyy [mm]] | [mm [yyyy]]\n\n");
    printf("yyyy\tyear of calendar\n");
    printf("mm\tmonth of calendar\n");
    printf("\nAuthor: Francis Asante <kofrasa@gmail.com> (2009)\n");
}

int get_days(int month) {
    switch (month) {
        case 2: return 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

/* checks whether a given year is a leap year */
int is_leap_year(int year) {
    return ((year % 4 == 0) && (!(year % 100 == 0) || (year % 400 == 0)));
}

void print_day(int day, DayOfWeek dayOfWeek) {
    /* for a first day, print tabs to get it to its correct position on the calendar */
    if (day == 1) {
        int i;
        for (i = 1; i < dayOfWeek; i++) 
            printf("%3s", "");
    }
    if (dayOfWeek == Saturday)
        printf("%2d\n", day);
    else
        printf("%2d ", day);
}

int get_frist_dayofweek(int year, int month) {
    if (year < MIN_YEAR){
        printf("Year is out of range.\n");
        return -1;
    }
    if (month < 0 || month > 12) {
        printf("Month is out of range.\n");
        return -1;
    }

    int indexYear;
    DayOfWeek dayOfWeek;

    if (year >= MIN_YEAR && year < MID_YEAR) {
        indexYear = MIN_YEAR;
        dayOfWeek = MIN_YEAR_DAY_OF_WEEK;
    } else {
        indexYear = MID_YEAR;
        dayOfWeek = MID_YEAR_DAY_OF_WEEK;
    }

    while (indexYear < year) { /* Find day of week of January 1st of the year */
        append_days(&dayOfWeek, (is_leap_year(indexYear)) ? 2 : 1);
        indexYear++;
    }

    int indexMonth = 1;
    while (indexMonth < month) {
        append_days(&dayOfWeek, (indexMonth == 2 && is_leap_year(year)) ? 29 : get_days(indexMonth));
        indexMonth++;
    }
    return dayOfWeek;
}

static void append_days(DayOfWeek *dayOfWeek, int days) {
    //TODO: should be improved with some mod arithmetic.
    while (days-- != 0)
        *dayOfWeek = (*dayOfWeek != 7) ? ++*dayOfWeek : 1;
}

int main(int argc, char **argv) {

    if (argc == 2 && (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        help();
        return 1;
    }

    time_t curr_time = time(NULL);
    struct tm* today = localtime(&curr_time);
    int days, month, year, all, temp;

    if (argc == 1) {
        year = today->tm_year + MIN_YEAR;
        month = today->tm_mon + 1;
    } else {
        /* check for invalid arguments */
        int i;
        for (i = 1; i < argc; i++) {
            char* str = argv[i];
            int len = strlen(str);
            while (len-- != 0) {
                if (!isdigit(toascii(*str++))) {
                    printf("Invalid arguments specified.\n");
                    return 1;
                }
            }
        }
        temp = atoi(argv[1]);
        if (temp < MIN_YEAR) {
            month = temp;
            year = (argc > 2) ? atoi(argv[2]) : today->tm_year + MIN_YEAR;
        } else {
            year = temp;
            month = (argc > 2) ? atoi(argv[2]) : 0;
        }
    }
    
    if (year < MIN_YEAR) {        
        printf("The year %d is not supported\n", year);
        return -1;
    }

    all = (month == 0) ? 1 : 0;
    month = (month == 0) ? 1 : month;
    DayOfWeek dayOfWeek = get_frist_dayofweek(year, month);
    if (dayOfWeek > 0) {
        if (all == 0) {
            printf("\n%10s %d\n", months[month - 1], year);
        } else {
            printf("\n%12d\n", year);
        }
        int i;
        do {
            days = (month == 2 && is_leap_year(year)) ? 29 : get_days(month);
            if (all != 0) 
                printf("\n      %s\n", months[month - 1]);
            
            printf("Su Mo Tu We Th Fr Sa\n");
            days++;
            for (i = 1; i < days; i++) {
                print_day(i, dayOfWeek);
                dayOfWeek = (dayOfWeek == Saturday) ? Sunday : ++dayOfWeek;
            }
            month++;
            printf("\n");
            /* print 2 lines after each month calendar */
        } while (month <= 12 && all != 0);
        printf("\nToday: %s\n\n", asctime(today));
        return 0;
    }
    return 1;
}
