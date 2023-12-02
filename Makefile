
TARGETS = d1p1 d1p2

all: $(TARGETS)

d1p1:
	cd day-01/part1 && $(MAKE)

d1p2:
	cd day-01/part2 && $(MAKE)


clean:
	cd day-01/part1 && $(MAKE) clean
	cd day-01/part2 && $(MAKE) clean
	rm -rf build