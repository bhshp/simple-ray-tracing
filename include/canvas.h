#pragma once

#ifndef CANVAS_H_
#define CANVAS_H_

struct canvas {
   public:
    constexpr canvas(int width, int height);

    constexpr double aspect_ratio() const;
    constexpr int width() const;
    constexpr int height() const;

   private:
    int width_;
    int height_;
    double aspect_ratio_;
};

constexpr inline canvas::canvas(int width, int height) : width_{width}, height_{height}, aspect_ratio_{1.0 * width / height} {}

constexpr inline double canvas::aspect_ratio() const { return aspect_ratio_; }

constexpr inline int canvas::width() const { return width_; }

constexpr inline int canvas::height() const { return height_; }

#endif  // CANVAS_H_