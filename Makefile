default: all

day1: day1.c
	cc -o day1 day1.c

day1_run: day1
	time ./day1

day2: day2.c
	cc -o day2 day2.c

day2_run: day2
	time ./day2

day3: day3.c
	cc -o day3 day3.c

day3_run: day3
	time ./day3

day4: day4.c
	cc -o day4 day4.c

day4_run: day4
	time ./day4

day5: day5.c
	cc -o day5 day5.c

day5_run: day5
	time ./day5

day6: day6.c
	cc -o day6 day6.c

day6_run: day6
	time ./day6

day7: day7.c
	cc -o day7 day7.c

day7_run: day7
	time ./day7

day8: day8.c
	cc -o day8 day8.c

day8_run: day8
	time ./day8

day9: day9.c
	cc -o day9 day9.c

day9_run: day9
	time ./day9

all: day1_run day2_run day3_run day4_run day5_run day6_run day7_run day8_run day9_run

clean:
	rm -f day1 day2 day3 day4 day5 day6 day7 day8 day9
