#include "progress_bar.h"

progress_bar::progress_bar(std::ostream& os, size_t num) : os_{os},
                                                           num_{num},
                                                           digits_{std::to_string(num_).length()},
                                                           index_{0},
                                                           start_time_{std::chrono::high_resolution_clock::now()} { output(0); }

progress_bar::~progress_bar() {
    os_ << to_length("\rProgress Complete  ", bar_length + 2 * digits_ + 26, false) << std::endl;
}

void progress_bar::operator++(int) {
    output(++index_);
}

void progress_bar::operator++() {
    output(++index_);
}

void progress_bar::output(size_t index) {
    size_t per = percentage(index);  // bar_length + 2 * digits_ + 16 + 10
    size_t block = static_cast<int>(1e-3 * per * bar_length);
    os_ << '\r' << "[" << bar(block) << "] " << to_2f(per) << ' '
        << to_length(index, digits_) << '/' << num_
        << "  eta: " << to_length(std::to_string(eta(index)).append("s"), 8, false) << std::flush;
}

std::string progress_bar::to_length(size_t n, size_t length, bool left) const {
    return to_length(std::to_string(n), length, left);
}

std::string progress_bar::to_length(const std::string& s, size_t length, bool left) const {
    if (s.length() < length) {
        std::string blank = std::string(length - s.length(), ' ');
        if (left) {
            return blank.append(s);
        }
        return s + blank;
    }
    return s;
}

std::string progress_bar::to_2f(size_t x) const {
    std::string res = std::to_string(x / 10);
    res.push_back('.');
    res.push_back(static_cast<char>('0' + x % 10));
    res.push_back('%');
    return to_length(res, 6, false);
}

std::string progress_bar::bar(size_t a) const {
    return to_length(std::string(a, '*'), bar_length, false);
}

size_t progress_bar::percentage(size_t a) const {
    return 1000 * a / num_;
}

int64_t progress_bar::eta(size_t index) {
    using namespace std::chrono;
    using namespace std::chrono_literals;
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    int64_t seconds = index == 0 ? 0 : (now - start_time_) / 1ms * (num_ - index);
    start_time_ = now;
    return seconds / 1000;
}
