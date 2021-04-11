#include "hittable_list.h"

#include "hittable.h"

hittable_list::hittable_list() {}

hittable_list::~hittable_list() {}

void hittable_list::push_back(const std::shared_ptr<hittable> &object) {
    list_.push_back(object);
}

void hittable_list::pop_back() {
    list_.pop_back();
}

void hittable_list::push_front(const std::shared_ptr<hittable> &object) {
    list_.push_front(object);
}

void hittable_list::pop_front() {
    list_.pop_front();
}

void hittable_list::clear() {
    list_.clear();
}

std::optional<hit_record> hittable_list::hit(const ray &r, double t_min, double t_max) const {
    std::optional<hit_record> result;
    double closest_so_far = t_max;
    for (const std::shared_ptr<hittable> &o : list_) {
        if (std::optional<hit_record> temp = o->hit(r, t_min, closest_so_far); temp.has_value()) {
            closest_so_far = temp->t();
            result = temp;
        }
    }
    return result;
}
