src_dir = ./src
target_dir = ./target

target = $(target_dir)/main.out
temp_image = $(target_dir)/out.ppm
target_image = $(target_dir)/out.jpg
current_image = $(target_dir)/current.jpg

CC = g++
CCFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic-errors -I./include -O3

src = $(wildcard $(src_dir)/*.cc)
object = $(patsubst $(src_dir)/%.cc,$(target_dir)/%.o,$(src))

all: $(target_image)
	code $(target_image)

$(target_image): $(target)
	$(target) && python -c "import cv2;cv2.imwrite('$(target_image)', cv2.imread('$(temp_image)'))"

$(target): $(object)
	$(CC) -o $@ $^ $(CCFLAGS)

$(target_dir)/%.o: $(src_dir)/%.cc
	$(CC) -c -o $@ $^ $(CCFLAGS)

build: 
	make $(target)

clean:
	$(RM) $(target_dir)/*.o $(target_image) $(target) $(temp_image)

new:
	make $(target_image) && cp -f $(target_dir)/out.jpg $(target_dir)/current.jpg && code $(current_image)

.PHONY: all clean new build
