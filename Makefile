src_dir = ./src
target_dir = ./target

target = $(target_dir)/main.out

temp_image = $(target_dir)/out.ppm
target_image = $(target_dir)/out.jpg

# 
# date +"%F %T"

CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -I./include -O2

src = $(wildcard $(src_dir)/*.cc)

all: $(target)
	$(target)
	python -c "import cv2;cv2.imwrite('$(target_image)', cv2.imread('$(temp_image)'))" && code $(target_image)
$(target):
	$(CC) -o $(target) $(src_dir)/main.cc $^ $(CCFLAGS)

clean:
	$(RM) $(target_dir)/*.o $(target_image) $(target) $(temp_image)

new:
	$(RM) $(target_dir)/current.jpg
	make all
	mv $(target_dir)/out.jpg $(target_dir)/current.jpg

.PHONY: all clean new
