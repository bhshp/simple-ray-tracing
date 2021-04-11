#include "util.h"

inline double sqr(double x) {
    return x * x;
}

inline double deg2rad(double deg) {
    return deg / 180.0 * pi;
}

inline double random_double() {
    static std::mt19937_64 gen{std::random_device{}()};
    static std::uniform_real_distribution<double> dis{0.0, 1.0};
    return dis(gen);
}

inline int color_cast(double c) {
    if (c <= 0) {
        return 0;
    } else if (c >= 1.0) {
        return 255;
    }
    return static_cast<int>(c * 256.0);
}