src = $(wildcard ./src/*.cc)
header = $(wildcard ./include/)
target = main.out
temp_image = out.ppm
target_image = out.jpg
CC = g++
CCFLAGS = -std=c++17 -O2 -Wall -Werror

$(target): $(src)
	$(CC) $(src) -I$(header) -o $(target) $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf ${temp_image};
	rm -rf $(target);
	rm -rf ${target_image};

.PHONY: run
run:
	make && ./$(target) && python ./src/main.py && code ./${target_image};
	# rm -rf ${temp_image};
	rm -rf $(target);

.PHONY: all
all:
	make clean;
	make run;
	date +"%F %T"
