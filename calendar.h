#ifndef __CALENDAR_H
#define __CALENDAR_H

#ifdef __cplusplus
extern "C" {
#endif

#define MIN_YEAR 1900 /* smallest year possible */
#define MID_YEAR 2000 /* intermediate year used to speed up computation */
#define MIN_YEAR_DAY_OF_WEEK 2 /* i.e 1st January 1900 was a Monday */
#define MID_YEAR_DAY_OF_WEEK 7 /* a Saturday */

typedef enum _dayOfWeek{
    Sunday = 1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
} DayOfWeek;

void help();
void print_day(int day, DayOfWeek dayOfWeek);
int get_days(int month);
int is_leap_year(int year);
int get_frist_dayofweek(int month, int year);
static void append_days(DayOfWeek*, int);

#ifdef __cplusplus
}
#endif

#endif /* __CALENDAR_H */
