#include "Tasks.h"

#include <fstream>
#include <cstddef>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

std::string read_file([[maybe_unused]] const std::filesystem::path& path)
{
// BEGIN: T1
// Write your answer to assignment T1 here, between the // BEGIN: T1
// and // END: T1 comments. Remove the code already there and replace it
// with your own.
    std::ifstream file {path};
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string contents;
    std::string line;
    while (std::getline(file, line)) {
        contents.append(line);
        contents.append("\n");
    }

    return contents;

// END: T1
}

std::vector<Measurement> read_measurements([[maybe_unused]] const std::filesystem::path& path)
{
// BEGIN: T2
// Write your answer to assignment T2 here, between the // BEGIN: T2
// and // END: T2 comments. Remove the code already there and replace it
// with your own.
    std::ifstream file{path};
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::vector<Measurement> measurements{};
    for (std::string name, value; file >> name >> value;) {
        if (name == " " || name == "\n") continue;
        if (value == " " || value == "\n") continue;
        measurements.emplace_back(Measurement{name, std::stof(value)});
    }

    return measurements;

// END: T2
}

bool write_report(
    [[maybe_unused]] const std::filesystem::path& path,
    [[maybe_unused]] const std::vector<Measurement>& measurements
)
{
// BEGIN: T3
// Write your answer to assignment T3 here, between the // BEGIN: T3
// and // END: T3 comments. Remove the code already there and replace it
// with your own.
    std::ofstream file {path};
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (const auto& m : measurements) {
        file << m.name << ":" << m.value << std::endl;
    }

    return true;
// END: T3
}

int random_int([[maybe_unused]] int min, [[maybe_unused]] int max)
{
// BEGIN: T4
// Write your answer to assignment T4 here, between the // BEGIN: T4
// and // END: T4 comments. Remove the code already there and replace it
// with your own.
    if (min > max) {
        throw std::invalid_argument("'min' can not be greater than 'max'");
    }

    std::random_device rd{"mt19937"};
    std::uniform_int_distribution<int>dist(min, max);

    return dist(rd);

// END: T4
}

std::vector<Measurement> generate_random_measurements(
    [[maybe_unused]] const std::string& name,
    [[maybe_unused]] int count,
    [[maybe_unused]] int min_value,
    [[maybe_unused]] int max_value
)
{
// BEGIN: T5
// Write your answer to assignment T5 here, between the // BEGIN: T5
// and // END: T5 comments. Remove the code already there and replace it
// with your own.
    if (count < 0) {
        throw std::invalid_argument("Count must be zero or a positive number");
    }
    std::vector<Measurement> out;
    for (int i{}; i < count; i++) {
        out.emplace_back(
            Measurement{
                name,
                static_cast<double>(random_int(min_value, max_value))
            }
        );
    }

    return out;

// END: T5
}

MeasurementSeries::MeasurementSeries(
    [[maybe_unused]] const std::string& name,
    [[maybe_unused]] const std::vector<double>& values
)
    : name_{}
    , values_{nullptr}
    , count_{}
{
// BEGIN: T6A
// Write your constructor answer here. Replace the TODO code with your own.
    name_ = name;
    count_ = values.size();
    if (count_ == 0)
        values_ = nullptr;

    values_ = new double[count_];
    for (size_t i{}; i < count_; i++) {
        values_[i] = values.at(i);
    }
// END: T6A
}

MeasurementSeries::~MeasurementSeries()
{
// BEGIN: T6B
    if (values_ == nullptr)
        return;

    delete[] values_;
// Write your destructor answer here. Replace the TODO code with your own.
// END: T6B
}

MeasurementSeries::MeasurementSeries([[maybe_unused]] const MeasurementSeries& other)
    : name_{}
    , values_{nullptr}
    , count_{}
{
// BEGIN: T6C
// Write your copy constructor answer here. Replace the TODO code with your own.
    name_ = other.name_;
    count_ = other.count_;
    values_ = new double[count_];

    for (size_t i{}; i < count_; i++) {
        values_[i] = other.values_[i];
    }
// END: T6C
}

const std::string& MeasurementSeries::name() const
{
    return name_;
}

std::size_t MeasurementSeries::size() const
{
    return count_;
}

double MeasurementSeries::at(const std::size_t index) const
{
    if (index >= count_) {
        throw std::out_of_range("MeasurementSeries index out of range");
    }

    return values_[index];
}

void MeasurementSeries::set(const std::size_t index, const double value)
{
    if (index >= count_) {
        throw std::out_of_range("MeasurementSeries index out of range");
    }

    values_[index] = value;
}

std::ostream& operator<<([[maybe_unused]] std::ostream& os, [[maybe_unused]] const MeasurementSeries& series)
{
// BEGIN: T6D
// Write your ostream operator<< answer here. Replace the TODO code with your own.
    os << series.name_ << ": ";
    for (int i{}; i < series.count_ - 1; i++) {
        os << series.values_[i] << ", ";
    }
    os << series.values_[series.count_ - 1];
    return os;
// END: T6D
}
