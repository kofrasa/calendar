

all: calendar

calendar: calendar.c calendar.h
	gcc -o calendar calendar.c calendar.h

clean:
	rm calendar
