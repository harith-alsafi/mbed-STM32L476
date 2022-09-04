#pragma once
#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

#define SP 1
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define WAIT 200ms
#define MAX_TEMP (float) 35.0
#define MIN_TEMP (float) 5.0
#define N_LIGHTS 3
#define N_DEVICES 2
#define N_APPLIANCES 3

/**
 * @brief Used to print on screen 
 * 
 * @return BufferedSerial 
 */
BufferedSerial pc(USBTX, USBRX);   

/**
 * @brief Joystick object
 * 
 * @return Joystick 
 */
Joystick joystick(PC_3, PC_2);  //attach and create joystick object

/**
 * @brief LCD Object
 * 
 * @return N5110 
 */
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

/**
 * @brief Right button 
 * 
 * @return DigitalIn 
 */
DigitalIn right_button(PC_10);

/**
 * @brief Left button
 * 
 * @return DigitalIn 
 */
DigitalIn left_button(PC_12);

/**
 * @brief Main button
 * 
 * @return DigitalIn 
 */
DigitalIn main_button(PC_11);

/**
 * @brief Potentiometer 
 * 
 * @return AnalogIn 
 */
AnalogIn pot(PC_0);

/**
 * @brief LDR sensor
 * 
 * @return AnalogIn 
 */
AnalogIn ldr_sensor(PA_1); //LDR pin

/**
 * @brief Tempreature sensor 
 * 
 * @return AnalogIn 
 */
AnalogIn tmp_sensor(PA_0); //TEMP Sensor pin

/**
 * @brief FSR 
 * 
 * @return AnalogIn 
 */
AnalogIn fsr_sensor(PA_4); //Force sensor pin

/**
 * @brief Buzzer 
 * 
 * @return PwmOut 
 */
PwmOut buzzer(PA_15);

/**
 * @brief Output devices
 * 
 * @return BusOut 
 */
BusOut devices_out(PA_12, PA_11); // works

/**
 * @brief Output appliances
 * 
 * @return BusOut 
 */
BusOut appliances_out(PB_15, PB_14, PB_13); // works

/**
 * @brief Output lights 
 * 
 */
PwmOut lights_out[N_LIGHTS] = {PwmOut(PC_8), PwmOut(PC_6), PwmOut(PB_8)};

/**
 * @brief AC
 * 
 * @return PwmOut 
 */
PwmOut ac_out(PC_9);

/**
 * @brief pages states
 * 
 */
enum State
{
    HOME,
    MAIN,
    STANDBY,
    SECURITY
};

/**
 * @brief MainPage options 
 * 
 */
enum Options
{
    CHANGE_TIME, // change time 
    CHANGE_FLAG, // change flags
    SETTINGS, // brightness and ac temp
    EDIT_PERIPHERALS // edit peripherals
};

/**
 * @brief Right arrow icon
 * 
 */
const int right_arrow[7][8] = {
    {1,0,0,0,1,0,0,0},
    {1,1,0,0,1,1,0,0},
    {1,1,1,0,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,0},
    {1,1,0,0,1,1,0,0},
    {1,0,0,0,1,0,0,0}
};

/**
 * @brief Home icon 
 * 
 */
const int home_icon[7][7] = {
    {0,0,0,1,0,0,0},
    {0,0,1,1,1,0,0},
    {0,1,1,1,1,1,0},
    {1,0,0,0,0,0,1},
    {1,0,1,1,1,0,1},
    {1,0,1,0,1,0,1},
    {1,1,1,1,1,1,1}
};

/**
 * @brief Light bulb icon
 * 
 */
const int light_icon[7][9] = {
    {0,0,1,1,1,0,0,0,0},
    {0,1,0,0,0,1,0,0,0},
    {1,0,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,0},
    {0,1,1,0,1,1,0,0,1},
    {0,0,1,1,1,0,0,0,0},
    {0,0,1,1,1,0,0,0,0}
};

/**
 * @brief AC icon
 * 
 */
const int ac_icon[7][11] = {
    {0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,0,0},
    {1,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,1,1,1,0,0,1,0,0},
    {1,1,1,1,1,1,1,1,1,0,1},
    {0,1,0,1,0,1,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0}
};

/**
 * @brief False icon 
 * 
 */
const int false_icon[7][7] = {
    {0,0,0,0,0,0,0},
    {0,1,0,0,0,1,0},
    {0,0,1,0,1,0,0},
    {0,0,0,1,0,0,0},
    {0,0,1,0,1,0,0},
    {0,1,0,0,0,1,0},
    {0,0,0,0,0,0,0}
};

/**
 * @brief Correct icon 
 * 
 */
const int correct_icon[7][9] = {
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1,0},
    {1,0,0,0,0,0,1,0,0},
    {0,1,0,0,0,1,0,0,0},
    {0,0,1,1,1,0,0,0,0},
    {0,0,0,1,0,0,0,0,0}
};

/**
 * @brief Lock icon 
 * 
 */
const int lock_icon[7][10] = {
    {0,0,0,1,1,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,0,0},
    {0,1,1,1,1,1,1,0,0,1},
    {1,0,0,1,1,0,0,1,0,0},
    {1,0,1,0,0,1,0,1,0,1},
    {1,0,0,1,1,0,0,1,0,0},
    {0,1,1,1,1,1,1,0,0,0}
};

/**
 * @brief Left arrow icon 
 * 
 */
const int left_arrow[7][8] = {
    {0,0,0,1,0,0,0,1},
    {0,0,1,1,0,0,1,1},
    {0,1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1,1},
    {0,1,1,1,0,1,1,1},
    {0,0,1,1,0,0,1,1},
    {0,0,0,1,0,0,0,1}
};

/**
 * @brief MainPage icon
 * 
 */
const int main_icon[7][7] = {
    {1,0,0,1,0,0,1},
    {0,1,1,1,1,1,0},
    {0,1,0,1,0,1,0},
    {1,1,1,1,1,1,1},
    {0,1,0,1,0,1,0},
    {0,1,1,1,1,1,0},
    {1,0,0,1,0,0,1}
};