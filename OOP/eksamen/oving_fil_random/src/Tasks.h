#pragma once

#include <cstddef>
#include <filesystem>
#include <ostream>
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

class MeasurementSeries {
public:
    MeasurementSeries(const std::string& name, const std::vector<double>& values);
    ~MeasurementSeries();
    MeasurementSeries(const MeasurementSeries& other);

    const std::string& name() const;
    std::size_t size() const;
    double at(std::size_t index) const;
    void set(std::size_t index, double value);

private:
    std::string name_;
    double* values_;
    std::size_t count_;

    friend std::ostream& operator<<(std::ostream& os, const MeasurementSeries& series);
};

std::ostream& operator<<(std::ostream& os, const MeasurementSeries& series);
