src = $(wildcard ./src/*.cc)
header = $(wildcard ./include/)
target = main.out
temp_image = ./target/out.ppm
target_image = ./target/out.jpg

CC = clang++
CCFLAGS = -std=c++17 -O2 -Wall -Werror -Wextra -pedantic-errors

$(target): $(src)
	$(CC) $(src) -I$(header) -o $(target) $(CCFLAGS)

.PHONY: clean
clean:
ifndef keep-temp
	rm -rf ${temp_image}
endif
	rm -rf $(target) ${target_image}

.PHONY: run
run:
	make
	time -f "%E elapsed." ./$(target)
	python -c "import cv2;cv2.imwrite('${target_image}', cv2.imread('${temp_image}'))" && code ./${target_image}
ifndef keep-temp
	rm -rf ${temp_image}
endif
	rm -rf $(target)

.PHONY: all
all:
	make clean
	make run
	date +"%F %T"
