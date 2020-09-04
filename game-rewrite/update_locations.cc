#pragma once

#include <random>
#include <time.h>

typedef int unit;

void generate_random_list(unit * arr, int size, const unit bound, std::mt19937 * seed_gen) {
    std::uniform_int_distribution<> dist(-bound, bound);
    for (auto i = 0; i < size; i++) {
        arr[i] = dist(seed_gen);
    }
}

void update_coords(unit** pos, unit** vec, const int size) {
    for(auto i = 0; i < 3; i++) {
        for(auto j = 0; j < size; j++) {
            pos[i][j] = pos[i][j] + vec[i][j];
        }
    }
}

int main(int argc, char** argv) {
    if(argc != 3) {
        printf("Required arguments: vector_length(N) and iterations_num(M)");
        return -1;
    }

    auto size = std::stoi(argv[0]);
    auto iters = std::stoi(argv[1]);
    std::hash<int> hash_int;
    std::mt19937 gen(hash_int(size));

    unit** pos = new unit*[3];
    unit** vec = new unit*[3];
    for(int i = 0; i < 3; i++){
        pos[i] = new unit[size];
        generate_random_list(pos[i], size, static_cast<unit>(1000.), &gen);
        vec[i] = new unit[size];
        generate_random_list(vec[i], size, static_cast<unit>(1.), &gen);
    }

    timespec t_start;
    timespec t_end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t_start);

    for(int i = 0; i < iters; i++) {
        update_coords(pos, vec, size);
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t_end);

    unit checksum = 0;
    for(auto i = 0; i < 3; i++) {
        checksum = std::accumulate(pos[0], pos[0] + size, checksum);
    }
    printf("Mean time per coordinate: %f", (1000000. * t_start.tv_nsec / (size * iters)));
    printf("Final checksum is: %d", checksum);


    for(auto i = 0; i < 3; i++) {
        delete pos[i];
        delete vec[i];
    }

    delete pos;
    delete vec;
    return 0;
}
