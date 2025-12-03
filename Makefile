default: all

day1: day1.c
	cc -o day1 day1.c

day2: day2.c
	cc -o day2 day2.c

day3: day3.c
	cc -o day3 day3.c

all: day1 day2 day3
	./day1
	./day2
	./day3

clean:
	rm -f day1 day2 day3
