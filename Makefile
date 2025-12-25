default: all

day1: day1.c
	cc -o day1 day1.c

day1run: day1
	time ./day1

day2: day2.c
	cc -o day2 day2.c

day2run: day2
	time ./day2

day3: day3.c
	cc -o day3 day3.c

day3run: day3
	time ./day3

day4: day4.c
	cc -o day4 day4.c

day4run: day4
	time ./day4

day5: day5.c
	cc -o day5 day5.c

day5run: day5
	time ./day5

day6: day6.c
	cc -o day6 day6.c

day6run: day6
	time ./day6

day7: day7.c
	cc -o day7 day7.c

day7run: day7
	time ./day7

day8: day8.c
	cc -o day8 day8.c

day8run: day8
	time ./day8

day9: day9.c
	cc -o day9 day9.c

day9run: day9
	time ./day9

all: day1run day2run day3run day4run day5run day6run day7run day8run day9run

clean:
	rm -f day1 day2 day3 day4 day5 day6 day7 day8 day9
