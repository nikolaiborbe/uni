#ifndef DEBOUNCEDINPUT_HPP_OSGDRPUG
#define DEBOUNCEDINPUT_HPP_OSGDRPUG

#include <cstdlib>
#include <cstdint>
#include <chrono>


template <int num_inputs, typename Clock = std::chrono::high_resolution_clock>
class DebouncedInput
{
public:
    void update(size_t index, bool state);
    
    bool is_key_down(size_t index) const;

    bool is_held(size_t index) const;

    bool is_initial_press(size_t index, bool state) const;

private:
    uint64_t timestamps[num_inputs]{false};
    bool inputs[num_inputs]{false};
};

template <int num_inputs, typename Clock>
void DebouncedInput<num_inputs, Clock>::update(size_t index, bool state)
{

    bool key_down = is_key_down(index);

    if ( ! key_down && state ) {
        timestamps[index] = static_cast<uint64_t>(Clock::now().time_since_epoch().count());
    }
    
    if ( key_down && ! state ) {
        timestamps[index] = 0;
    }

    inputs[index] = state;
}

template <int num_inputs, typename Clock>
bool DebouncedInput<num_inputs, Clock>::is_key_down(size_t index) const
{
    return inputs[index];
}

template <int num_inputs, typename Clock>
bool DebouncedInput<num_inputs, Clock>::is_held(size_t index) const
{
    auto current_ts = Clock::now().time_since_epoch().count();

    return is_key_down(index) && (current_ts - static_cast<long>(timestamps[index]) > 1000000000);

}

template <int num_inputs, typename Clock>
bool DebouncedInput<num_inputs, Clock>::is_initial_press(size_t index, bool state) const
{
    return ! is_key_down(index) && state;
}

template 
class DebouncedInput<256, std::chrono::high_resolution_clock>;

typedef DebouncedInput<256, std::chrono::high_resolution_clock> DebouncedKBInput;


#endif /* end of include guard: DEBOUNCEDINPUT_HPP_OSGDRPUG */


