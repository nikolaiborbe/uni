#pragma once

#include <filesystem>
#include <string>
#include <vector>

struct Measurement {
    std::string name;
    double value;
};

std::string read_file(const std::filesystem::path& path);

std::vector<Measurement> read_measurements(const std::filesystem::path& path);

bool write_report(const std::filesystem::path& path, const std::vector<Measurement>& measurements);

int random_int(int min, int max);

std::vector<Measurement> generate_random_measurements(
    const std::string& name,
    int count,
    int min_value,
    int max_value
);
