#ifndef THRUSTERS_CONTROLLER_H
#define THRUSTERS_CONTROLLER_H
#include <string>
#include <vector>
#include <fstream>

extern int number_of_thrusters;
extern int max_thrust;
extern int min_thrust;
extern int full_thrust;
extern int zero_thrust_pwm;
extern int min_pwm;
extern int max_pwm;
extern std::vector<float> surge_vector_init, sway_vector_init, heave_vector_init, yaw_vector_init, pitch_vector_init, roll_vector_init;

namespace ThrustersController{
    void init();
    void writeThrusterValues(float* thrust_vector);
    void refresh();
    void shutdown();
}
#endif