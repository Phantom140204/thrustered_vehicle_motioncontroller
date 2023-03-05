#ifndef VEHICLE_CONFIG_H
#define VEHICLE_CONFIG_H

#define NUMBER_OF_THRUSTERS 6

#define MAX_THRUST 100
#define MIN_THRUST -100
#define FULL_THRUST 100
#define ZERO_THRUST_PWM 150
#define MIN_PWM 110
#define MAX_PWM 190

#define SURGE_VECTOR {1,0,1,1,0,1}
#define SWAY_VECTOR {1,0,1,-1,0,-1}
#define HEAVE_VECTOR {0,1,0,0,1,0}
#define YAW_VECTOR {1,0,-1,1,0,-1}
#define PITCH_VECTOR {0,0,0,0,0,0} 
#define ROLL_VECTOR {0,1,0,0,-1,0}


#endif