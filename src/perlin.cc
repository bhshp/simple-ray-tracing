#include "perlin.h"

perlin::perlin() : random_vec_{},
                   perm_x_{generate_and_shuffle()},
                   perm_y_{generate_and_shuffle()},
                   perm_z_{generate_and_shuffle()} {
    for (vec &x : random_vec_) {
        x = random_unit_vector();
    }
}

perlin::~perlin() {}

double perlin::noise(const point &p) const {
    int i = static_cast<int>(4 * p.x()) & 255;
    int j = static_cast<int>(4 * p.y()) & 255;
    int k = static_cast<int>(4 * p.z()) & 255;
    vec res = random_vec_[perm_x_[i] ^ perm_y_[j] ^ perm_z_[k]];
    return atan2(res.y(), res.x()) / pi;
}

std::array<int, perlin::point_count> perlin::generate_and_shuffle() {
    static std::mt19937_64 gen(std::random_device{}());
    std::array<int, point_count> res;
    std::iota(res.begin(), res.end(), 0);
    std::shuffle(res.begin(), res.end(), gen);
    return res;
}

double perlin::calculate_noise(const point &p) const {
    int i_x = static_cast<int>(std::floor(p.x())),
        i_y = static_cast<int>(std::floor(p.y())),
        i_z = static_cast<int>(std::floor(p.z()));  // integer part
    double f_x = p.x() - i_x,
           f_y = p.y() - i_y,
           f_z = p.z() - i_z;  // fraction part
    double g_x = sqr(f_x) * (3 - 2 * f_x),
           g_y = sqr(f_y) * (3 - 2 * f_y),
           g_z = sqr(f_z) * (3 - 2 * f_z);  // Hermitian smooth part
    double sum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                sum += (i * g_x + (1.0 - i) * (1 - g_x)) *
                       (j * g_y + (1.0 - j) * (1 - g_y)) *
                       (k * g_z + (1.0 - k) * (1 - g_z)) *
                       (random_vec_[perm_x_[(i_x + i) & 255] ^
                                    perm_y_[(i_y + j) & 255] ^
                                    perm_z_[(i_z + k) & 255]] *
                        vec{f_x - i, f_y - j, f_z - k});
            }
        }
    }
    return sum;
}

smooth_perlin::smooth_perlin() {}

smooth_perlin::~smooth_perlin() {}

double smooth_perlin::noise(const point &p) const {
    return calculate_noise(p);
}

turbulance_perlin::turbulance_perlin() : depth_{7} {}

turbulance_perlin::turbulance_perlin(int depth) : depth_{depth} {}

turbulance_perlin::~turbulance_perlin() {}

double turbulance_perlin::noise(const point &p) const {
    double res = 0;
    point temp = p;
    double weight = 1;
    for (int i = 0; i < depth_; i++) {
        res += weight * calculate_noise(temp);
        weight *= 0.5;
        temp *= 2;
    }
    return std::fabs(res);
}
