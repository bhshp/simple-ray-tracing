#include "const.h"

extern const double inf = std::numeric_limits<double>::infinity();
extern const double pi = std::acos(-1.0);
extern const double eps = 1e-8;

double sqr(double x) {
    return x * x;
}

double deg2rad(double deg) {
    return deg / 180.0 * pi;
}

int random_int(int a, int b) {
    static std::mt19937_64 gen{std::random_device{}()};
    return std::uniform_int_distribution<int>{a, b}(gen);
}

double random_double() {
    return random_double(0.0, 1.0);
}

double random_double(double a, double b) {
    static std::mt19937_64 gen{std::random_device{}()};
    return std::uniform_real_distribution<double>{a, b}(gen);
}

int color_cast(double c) {
    if (std::isnan(c)) {
        return 0;
    } else if (c > 0 && c < 1) {
        return static_cast<int>(c * 256.0);
    }
    return c <= 0 ? 0 : 255;
}

double clamp(double a, double min, double max) {
    if (a > min && a < max) {
        return a;
    }
    return a <= min ? min : max;
}

int clamp(int a, int min, int max) {
    if (a > min && a < max) {
        return a;
    }
    return a <= min ? min : max;
}
