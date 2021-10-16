#pragma once

#ifndef PROGRESS_BAR_H_
#define PROGRESS_BAR_H_

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

struct progress_bar {
   public:
    progress_bar(std::ostream& os, size_t num);
    ~progress_bar();

    void operator++(int);
    void operator++();

   private:
    void output(size_t index);

    std::string to_length(size_t n, size_t length, bool left = true) const;

    std::string to_length(const std::string& s, size_t length, bool left = true) const;

    std::string to_2f(size_t x) const;

    std::string bar(size_t a) const;

    size_t percentage(size_t a) const;

    int64_t eta(size_t index);

    const size_t bar_length = 50;

    std::ostream& os_;
    size_t num_;
    size_t digits_;
    size_t index_;
    std::chrono::high_resolution_clock::time_point start_time_;
};

#endif  // PROGRESS_BAR_H_
