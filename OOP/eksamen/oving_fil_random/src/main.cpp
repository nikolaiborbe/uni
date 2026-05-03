#include "Tasks.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

void assert_throws_runtime_error()
{
    bool threw = false;
    try {
        (void)read_file("data/does_not_exist.txt");
    } catch (const std::runtime_error&) {
        threw = true;
    }
    assert(threw);
}

void test_read_file()
{
    const std::string content = read_file("data/message.txt");
    assert(content.find("Dette er en liten testfil.") != std::string::npos);
    assert(content.find("Linje nummer to.") != std::string::npos);
    assert_throws_runtime_error();
}

void test_read_measurements()
{
    const std::vector<Measurement> measurements = read_measurements("data/measurements.txt");
    assert(measurements.size() == 4);
    assert(measurements.at(0).name == "temperature");
    assert(measurements.at(0).value == 18.5);
    assert(measurements.at(3).name == "pressure");
    assert(measurements.at(3).value == 1012.0);
}

void test_write_report()
{
    std::filesystem::create_directories("generated");

    const std::vector<Measurement> measurements{
        {"temperature", 20.0},
        {"humidity", 44.5},
        {"pressure", 1011.0},
    };

    assert(write_report("generated/report.txt", measurements));

    const std::string report = read_file("generated/report.txt");
    assert(report.find("temperature:20") != std::string::npos);
    assert(report.find("humidity:44.5") != std::string::npos);
    assert(report.find("pressure:1011") != std::string::npos);
}

void test_random_int()
{
    for (int i = 0; i < 200; ++i) {
        const int value = random_int(3, 7);
        assert(value >= 3);
        assert(value <= 7);
    }

    assert(random_int(5, 5) == 5);

    bool threw = false;
    try {
        (void)random_int(10, 1);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
}

void test_generate_random_measurements()
{
    const std::vector<Measurement> measurements =
        generate_random_measurements("temperature", 25, -10, 30);

    assert(measurements.size() == 25);
    for (const Measurement& measurement : measurements) {
        assert(measurement.name == "temperature");
        assert(measurement.value >= -10.0);
        assert(measurement.value <= 30.0);
    }

    bool threw = false;
    try {
        (void)generate_random_measurements("temperature", -1, 0, 10);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
}

} // namespace

int main()
{
    try {
        test_read_file();
        test_read_measurements();
        test_write_report();
        test_random_int();
        test_generate_random_measurements();
    } catch (const std::exception& error) {
        std::cerr << "En test stoppet med exception: " << error.what() << '\n';
        return 1;
    }

    std::cout << "Alle testene passerte.\n";
    return 0;
}
