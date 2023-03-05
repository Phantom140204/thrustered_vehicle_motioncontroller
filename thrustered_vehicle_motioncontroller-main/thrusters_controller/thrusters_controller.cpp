#include "thrusters_controller.h"
#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"
#include <iostream>
#include <vector>
#include <fstream>


ros::NodeHandle* nh;
ros::Publisher* pwm_pub;
std_msgs::Int32MultiArray* pwm_msg;
float limitToRange(float value, float minimum, float maximum);

int number_of_thrusters, max_thrust, min_thrust, full_thrust, zero_thrust_pwm, min_pwm, max_pwm;
std::vector<float> surge_vector_init, sway_vector_init, heave_vector_init, yaw_vector_init, pitch_vector_init, roll_vector_init;

std::string readValue(std::fstream& file){
	std::string line;
	std::getline(file,line);
	std::string str = line.substr(line.find(' ',8)+1);
	return str;
}

void setVariables(){
    std::fstream file("/home/phantom1402/ros/test_ws/src/testcode/src/thrustered_vehicle_motioncontroller-main/vehicle_config.h");
    readValue(file); readValue(file); readValue(file); //Omits the header guards
    
    number_of_thrusters = std::stoi(readValue(file));

    readValue(file); //Omits newline
    
    max_thrust = std::stoi(readValue(file));
    min_thrust = std::stoi(readValue(file));
    full_thrust = std::stoi(readValue(file));
    zero_thrust_pwm = std::stoi(readValue(file));
    min_pwm = std::stoi(readValue(file));
    max_pwm = std::stoi(readValue(file));

    readValue(file); //Omits newline

    //Set surge vector
    std::string value = readValue(file);
    std::string intValue = "";
    int i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			surge_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}
    //Set sway vector
    value = readValue(file);
    intValue = ""; i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			sway_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}
    //Set heave vector
    value = readValue(file);
    intValue = ""; i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			heave_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}
    //Set yaw vector
    value = readValue(file);
    intValue = ""; i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			yaw_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}
    //Set pitch vector
    value = readValue(file);
    intValue = ""; i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			pitch_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}
    //Set roll vector
    value = readValue(file);
    intValue = ""; i = 1;
    while(value[i]!='}'){
		if(value[i]!=',')
			intValue+=value[i];
		else{
			roll_vector_init.push_back(std::stoi(intValue));
			intValue="";
		}
		i++;
	}

    file.close(); //Close the file

    std::cout<<number_of_thrusters<<'\n';
	std::cout<<max_pwm<<'\n';
	std::cout<<min_pwm<<'\n';
	for(int i=0;i<surge_vector_init.size();i++){
		std::cout<<surge_vector_init[i]<<' ';
	}
	std::cout<<'\n';
	for(int i=0;i<sway_vector_init.size();i++){
		std::cout<<sway_vector_init[i]<<' ';
	}
	std::cout<<'\n';
	for(int i=0;i<heave_vector_init.size();i++){
		std::cout<<heave_vector_init[i]<<' ';
	}
	std::cout<<'\n';
	for(int i=0;i<yaw_vector_init.size();i++){
		std::cout<<yaw_vector_init[i]<<' ';
	}
	std::cout<<'\n';
	for(int i=0;i<pitch_vector_init.size();i++){
		std::cout<<pitch_vector_init[i]<<' ';
	}
	std::cout<<'\n';
	for(int i=0;i<roll_vector_init.size();i++){
		std::cout<<roll_vector_init[i]<<' ';
	}
	std::cout<<'\n';
}

void ThrustersController::init(){
    int argc = 0;
    ros::init(argc,NULL,"thrusters_controller");
    nh = new ros::NodeHandle;
    pwm_pub = new ros::Publisher;
    pwm_msg = new std_msgs::Int32MultiArray;
    *pwm_pub = nh->advertise<std_msgs::Int32MultiArray>("/pwm_values",50);
    setVariables();
    pwm_msg->data.resize(number_of_thrusters);


}

void ThrustersController::writeThrusterValues(float* thrust_vector){
    for (int i = 0; i < number_of_thrusters; i++)
    {   
         
         pwm_msg->data[i] = zero_thrust_pwm + thrust_vector[i]* (max_pwm - zero_thrust_pwm)/full_thrust;
         pwm_msg->data[i] = limitToRange(pwm_msg->data[i],min_pwm,max_pwm);
    }
    pwm_pub->publish(*pwm_msg);
}


void ThrustersController::refresh(){
    ros::spinOnce();
}


void ThrustersController::shutdown(){
    delete nh;
    delete pwm_pub;
    delete pwm_msg;

}


float limitToRange(float value, float minimum, float maximum){
    if (value > maximum){
        return maximum;
    }
    else if (value < minimum){
        return minimum;
    }
    else{
        return value;
    }
}