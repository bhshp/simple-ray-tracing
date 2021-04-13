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

    const size_t bar_length = 60;

    std::ostream& os_;
    size_t num_;
    size_t digits_;
    size_t index_;
    std::chrono::high_resolution_clock::time_point start_time_;
};

inline progress_bar::progress_bar(std::ostream& os, size_t num) : os_{os},
                                                               num_{num},
                                                               digits_{std::to_string(num_).length()},
                                                               index_{0},
                                                               start_time_{std::chrono::high_resolution_clock::now()} { output(0); }

inline progress_bar::~progress_bar() {
    os_ << to_length("\rProgress Complete  ", bar_length + 2 * digits_ + 26, false) << std::endl;
}

inline void progress_bar::operator++(int) {
    output(++index_);
}

inline void progress_bar::operator++() {
    output(++index_);
}

inline void progress_bar::output(size_t index) {
    size_t per = percentage(index);  // bar_length + 2 * digits_ + 16 + 10
    size_t block = static_cast<int>(1e-3 * per * bar_length);
    os_ << '\r' << "[" << bar(block) << "] " << to_2f(per) << ' '
        << to_length(index, digits_) << '/' << num_
        << "  eta: " << to_length(std::to_string(eta(index)).append("s"), 8, false) << std::flush;
}

inline std::string progress_bar::to_length(size_t n, size_t length, bool left) const {
    return to_length(std::to_string(n), length, left);
}

inline std::string progress_bar::to_length(const std::string& s, size_t length, bool left) const {
    if (s.length() < length) {
        std::string blank = std::string(length - s.length(), ' ');
        if (left) {
            return blank.append(s);
        }
        return s + blank;
    }
    return s;
}

inline std::string progress_bar::to_2f(size_t x) const {
    std::string res = std::to_string(x / 10);
    res.push_back('.');
    res.push_back(static_cast<char>('0' + x % 10));
    res.push_back('%');
    return to_length(res, 6, false);
}

inline std::string progress_bar::bar(size_t a) const {
    return to_length(std::string(a, '*'), bar_length, false);
}

inline size_t progress_bar::percentage(size_t a) const {
    return 1000 * a / num_;
}

inline int64_t progress_bar::eta(size_t index) {
    using namespace std::chrono;
    using namespace std::chrono_literals;
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    int64_t seconds = index == 0 ? 0 : (now - start_time_) / 1ms * (num_ - index);
    start_time_ = now;
    return seconds / 1000;
}

#endif  // PROGRESS_BAR_H_
