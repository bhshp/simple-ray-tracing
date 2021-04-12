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
    std::string to_2f(int x) {
        std::string res = std::to_string(x / 10);
        res.push_back('.');
        res.push_back(static_cast<char>('0' + x % 10));
        res.push_back('%');
        if (res.size() < 6) {
            res.append(std::string(6 - res.size(), ' '));
        }
        return res;
    }

    std::string bar(int a) {
        return std::string(a, '*').append(std::string(bar_length - a, ' '));
    }

    int percentage(int a) {
        return 1000 * a / num_;
    }

    const int bar_length = 100;

    std::ostream& os_;
    int num_;
};

progress_bar::progress_bar(std::ostream& os, int num) : os_{os}, num_{num} { os_.precision(2); }

void progress_bar::output(int index) {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    int per = percentage(num_ - index);
    int block = static_cast<int>(1e-3 * per * bar_length);
    os_ << '\r' << "[" << bar(block) << "] " << to_2f(per) << ' ' << num_ - index << '/' << num_ << std::flush;
}

void progress_bar::complete() {
    os_ << "\rComplete!  " << std::string(bar_length + 2 * std::to_string(num_).length(), ' ') << std::endl;
}

#endif  // PROGRESS_BAR_H_
