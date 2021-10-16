#include "texture.h"

texture::~texture() {}

solid_color_texture::solid_color_texture() {}

solid_color_texture::solid_color_texture(const color &c) : color_{c} {}

solid_color_texture::solid_color_texture(double r, double g, double b) : color_{r, g, b} {}

solid_color_texture::~solid_color_texture() {}

color solid_color_texture::value(double, double, const point &) const { return color_; }

checker_board_texture::checker_board_texture() {}

checker_board_texture::checker_board_texture(const std::shared_ptr<texture> even,
                                             const std::shared_ptr<texture> odd) : even_{even}, odd_{odd} {}

checker_board_texture::checker_board_texture(const color &a,
                                             const color &b) : even_{std::make_shared<solid_color_texture>(a)},
                                                               odd_{std::make_shared<solid_color_texture>(b)} {}

color checker_board_texture::value(double u, double v, const point &p) const {
    return (std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z()) < 0 ? odd_ : even_)->value(u, v, p);
}

noise_texture::noise_texture(double scale,
                             const std::shared_ptr<perlin> &p) : scale_{scale},
                                                                 noise_{p} {}

noise_texture::~noise_texture() {}

color noise_texture::value(double, double, const point &p) const {
    return (noise_->noise(scale_ * p) + 1) * 0.5 * color{1, 1, 1};
}

marble_texture::marble_texture(double scale,
                               const std::shared_ptr<perlin> &p) : scale_{scale},
                                                                   noise_{p} {}

marble_texture::~marble_texture() {}

color marble_texture::value(double, double, const point &p) const {
    return 0.5 * (1 + std::sin(scale_ * p.z() + 10 * noise_->noise(p))) * color{1, 1, 1};
}

image_texture::image_texture() : data_{}, width_{0}, height_{0} {}

image_texture::image_texture(const char *const path) {
    const double ratio = 1.0 / 255.0;
    std::ifstream in{path};
    if (!in.is_open()) {
        std::cerr << "File " << path << " Not Exist" << std::endl;
        return;
    }
    in.tie(nullptr);
    std::string type;
    if (!(in >> type) || type != "P3") {
        return;
    }
    if (!(in >> width_) || !(in >> height_)) {
        return;
    }
    if (!(in >> type) || type != "255") {
        return;
    }
    data_.resize(height_);
    for (size_t i = height_ - 1;; i--) {
        data_[i].resize(width_);
        for (size_t j = 0; j < width_; j++) {
            int r, g, b;
            if (!(in >> r) || !(in >> g) || !(in >> b)) {
                data_.clear();
                decltype(data_){}.swap(data_);
                return;
            }
            data_[i][j] = color{b * ratio, r * ratio, g * ratio};
        }
        if (i == 0) {
            break;
        }
    }
}

image_texture::~image_texture() {}

color image_texture::value(double u, double v, const point &) const {
    if (data_.empty()) {
        return color{1, 1, 1};
    }
    int i = clamp(static_cast<int>(clamp(v, 0.0, 1.0) * height_), 0, height_ - 1);
    int j = clamp(static_cast<int>(clamp(u, 0.0, 1.0) * width_), 0, width_ - 1);
    return data_[i][j];
}
