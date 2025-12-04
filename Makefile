default: all

day1: day1.c
	cc -o day1 day1.c

day2: day2.c
	cc -o day2 day2.c

day3: day3.c
	cc -o day3 day3.c

day4: day4.c
	cc -o day4 day4.c

all: day1 day2 day3 day4
	time ./day1
	time ./day2
	time ./day3
	time ./day4

clean:
	rm -f day1 day2 day3 day4
