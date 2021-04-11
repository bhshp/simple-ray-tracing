src_dir = ./src
target_dir = ./target

src = $(wildcard $(src_dir)/*.cc)
target = $(target_dir)/main.out

obj = $(patsubst $(src_dir)/%.cc,$(target_dir)/%.o,$(src))

temp_image = $(target_dir)/out.ppm
target_image = $(target_dir)/out.jpg

# python -c "import cv2;cv2.imwrite('$(target_image)', cv2.imread('$(temp_image)'))" && code ./$(target_image)
# date +"%F %T"

CC = g++
CCFLAGS = -std=c++17 -O2 -Wall -Wextra -Werror -pedantic-errors

all: $(target)
$(target): $(obj)
	$(CC) -o $@ $^ $(CCFLAGS)
$(target_dir)/%.o: $(src_dir)/%.cc
	$(CC) -c $^ -I./include -o $@ $(CCFLAGS)
clean:
	rm -rf $(obj)

.PHONY: all clean