#pragma once 
class Bed_Distance_sensor_level {
private: 

public: 
int BDsensor_config;
 int homing;
 static void echo_name(); 
void init(unsigned char _sda,unsigned char _scl,int delay_s); 
void BD_sensor_process(void); 
}; // class Bed_Distance_sensor_level 

extern Bed_Distance_sensor_level BD_Level;