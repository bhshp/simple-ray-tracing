#pragma once

#ifndef PROGRESS_BAR_H_
#define PROGRESS_BAR_H_

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

struct progress_bar {
   public:
    progress_bar(std::ostream& os, int num);

    void output(int index);

    void complete();

   private:
    std::string bar(int a, int b) {
        return std::string(a, '*').append(std::string(b - a, ' '));
    }

    double percentage(double a, double b) {
        return 100.0 * a / b;
    }

    const int bar_length = 100;

    std::ostream& os_;
    int num_;
};

progress_bar::progress_bar(std::ostream& os, int num) : os_{os}, num_{num} { os_.precision(2); }

void progress_bar::output(int index) {
    using namespace std::chrono;
    using namespace std::chrono_literals;
    os_.precision(2);
    time_point begin = high_resolution_clock::now();
    double per = percentage(num_ - index, num_);
    int block = static_cast<int>(per);
    os_ << '\r' << std::right << std::setw(4) << per << "% [" << bar(block, bar_length)
        << "] current: " << num_ - index << '/' << num_ << std::flush;
    time_point end = high_resolution_clock::now();
    if (end - begin < 50ms) {
        std::this_thread::sleep_for(50ms - (end - begin));
    }
}

void progress_bar::complete() {
    os_ << "\rComplete! " << std::string(bar_length + 5, ' ') << std::endl;
}

#endif  // PROGRESS_BAR_H_