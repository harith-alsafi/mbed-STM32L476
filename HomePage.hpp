#pragma once
#include "Speaker.hpp"

/**
 * @brief Home Page class
 * 
 */
class HomePage
{
    private:
        /**
         * @brief Total number of appliaces
         * 
         */
        int total_appliances;

        /**
         * @brief Total number of operating appliances
         * 
         */
        int operating_appliances;

        /**
         * @brief Total number of devices 
         * 
         */
        int total_devices;

        /**
         * @brief Total number of operating devices 
         * 
         */
        int operating_devices;
        
        /**
         * @brief Total number of lights
         * 
         */
        int total_lights;

        /**
         * @brief Total number of operating lights
         * 
         */
        int operating_lights;

        /**
         * @brief Contains state for appliances
         * 
         */
        std::vector<bool> appliances;

        /**
         * @brief Contains state for devices
         * 
         */
        std::vector<bool> devices;

        /**
         * @brief Contains state for lights
         * 
         */
        std::vector<bool> lights;

        /**
         * @brief Security mode flag
         * 
         */
        bool security_mode;

        /**
         * @brief Auto light mode flag
         * 
         */
        bool auto_light;

        /**
         * @brief Auto AC mode flag
         * 
         */
        bool auto_ac;

        /**
         * @brief The AC tempreature
         * 
         */
        float ac_temp;

        /**
         * @brief The measured tempreature
         * 
         */
        float actual_temp;

        /**
         * @brief The time object
         * 
         */
        struct tm time;

        /**
         * @brief Get number of turned on objects for given vector
         * 
         * @param a 
         * @return int 
         */
        int get_on(std::vector<bool> a){
            int count = 0;
            for(int i = 0; i < a.size(); i++){
                if(a[i] == 1){
                    count++;
                }
            }
            return count; 
        }

        /**
         * @brief Assigns the number of operating peripherals
         * 
         */
        void check_on(){
            operating_appliances = get_on(appliances);
            operating_devices = get_on(devices);
            operating_lights = get_on(lights);
        }

    public:
        /**
         * @brief Construct a new Home Page object
         * 
         */
        HomePage(){
            operating_lights = 0;
            operating_appliances = 0;
            operating_devices = 0;
        
            security_mode = true;
            auto_light = false;
            auto_ac = true;

            appliances.resize(N_APPLIANCES, 0);
            devices.resize(N_DEVICES, 0);
            lights.resize(N_LIGHTS, 0);

            ac_temp = 24.0;
            actual_temp = 25.0;
        }

        /**
         * @brief Resets devices 
         * 
         */
        void reset_devices(){
            for(int i = 0; i < N_DEVICES; i++){
                devices_out[i] = devices[i];
            }
        }

        /**
         * @brief Resets appliances 
         * 
         */
        void reset_appliances(){
            for(int i = 0; i < N_APPLIANCES; i++){
                appliances_out[i] = appliances[i];
            }
        }

        /**
         * @brief Resets lights 
         * 
         */
        void reset_lights(){
            for(int i = 0; i < N_LIGHTS; i++){
                lights_out[i] = lights[i];
            }
        }

        /**
         * @brief Recets AC value
         * 
         */
        void reset_ac(){
            ac_out.write((ac_temp-MIN_TEMP)/(MAX_TEMP-MIN_TEMP));
        }

        /**
         * @brief Set the total appliances 
         * 
         * @param n 
         */
        void set_total_appliances(int n){
            appliances.resize(n);
        }

        /**
         * @brief Set the total devices 
         * 
         * @param n 
         */
        void set_total_devices(int n){
            devices.resize(n);
        }

        /**
         * @brief Set the total lights 
         * 
         * @param n 
         */
        void set_total_lights(int n){
            lights.resize(n);
        }

        /**
         * @brief Set the auto light flag
         * 
         * @param flag 
         */
        void set_auto_light(bool flag){
            auto_light = flag;
        }

        /**
         * @brief Set the security mode flag
         * 
         * @param flag 
         */
        void set_security_mode(bool flag){
            security_mode = flag;
        }

        /**
         * @brief Set the auto ac flag
         * 
         * @param flag 
         */
        void set_auto_ac(bool flag){
            auto_ac = flag;
        }

        /**
         * @brief Set the ac tempreature
         * 
         * @param val 
         */
        void set_ac_temp(float val){
            ac_temp = val;
            reset_ac();
        }

        /**
         * @brief Set the actual tempreature
         * 
         * @param val 
         */
        void set_actual_temp(float val){
            actual_temp = val;
        }

        /**
         * @brief Set the time date object
         * 
         * @param hour 
         * @param mins 
         * @param day 
         * @param month 
         * @param year 
         */
        void set_time_date(int hour, int mins, int day, int month, int year){
            time.tm_hour = hour;
            time.tm_min = mins;
            time.tm_sec = 0;
            time.tm_year = year-1900;
            time.tm_mon = month-1;
            time.tm_mday = day;    
            set_time(mktime(&time));
        }

        /**
         * @brief Set the time only object
         * 
         * @param hour 
         * @param mins 
         */
        void set_time_only(int hour, int mins){
            time.tm_hour = hour;
            time.tm_min = mins;
            time.tm_sec = 0; 
            set_time(mktime(&time));
        }

        /**
         * @brief Set the date only object
         * 
         * @param day 
         * @param month 
         * @param year 
         */
        void set_date_only(int day, int month, int year){
            time.tm_year = year-1900;
            time.tm_mon = month-1;
            time.tm_mday = day;    
            set_time(mktime(&time));
        }

        /**
         * @brief Set the devices object
         * 
         * @param a 
         */
        void set_devices(std::vector<bool> a){
            devices = a;
            reset_devices();
        }

        /**
         * @brief Set the lights object
         * 
         * @param a 
         */
        void set_lights(std::vector<bool> a){
            lights = a;
            reset_lights();
        }

        /**
         * @brief Set the appliances object
         * 
         * @param a 
         */
        void set_appliances(std::vector<bool> a){
            appliances = a;
            reset_appliances();
        }

        /**
         * @brief Get the auto light flag
         * 
         * @return true 
         * @return false 
         */
        bool get_auto_light(){
            return auto_light;
        }

        /**
         * @brief Get the security mode flag
         * 
         * @return true 
         * @return false 
         */
        bool get_security_mode(){
            return security_mode;
        }

        /**
         * @brief Get the auto ac tempreature
         * 
         * @return true 
         * @return false 
         */
        bool get_auto_ac(){
            return auto_ac;
        }

        /**
         * @brief Get the year 
         * 
         * @return int 
         */
        int get_year(){
            return time.tm_year+1900;
        }

        /**
         * @brief Get the month 
         * 
         * @return int 
         */
        int get_month(){
            return time.tm_mon+1;
        }

        /**
         * @brief Get the day 
         * 
         * @return int 
         */
        int get_day(){
            return time.tm_mday;
        }

        /**
         * @brief Get the hour 
         * 
         * @return int 
         */
        int get_hour(){
            return time.tm_hour;
        }

        /**
         * @brief Get the minute 
         * 
         * @return int 
         */
        int get_minute(){
            return time.tm_min;
        }

        /**
         * @brief Get the actual tempreature
         * 
         * @return float 
         */
        float get_temp(){
            return actual_temp;
        }

        /**
         * @brief Get the devices object
         * 
         * @return std::vector<bool> 
         */
        std::vector<bool> get_devices(){
            return devices;
        }

        /**
         * @brief Get the lights object
         * 
         * @return std::vector<bool> 
         */
        std::vector<bool> get_lights(){
            return lights;
        }

        /**
         * @brief Get the appliances object
         * 
         * @return std::vector<bool> 
         */
        std::vector<bool> get_appliances(){
            return appliances;
        }

        /**
         * @brief Shows the page
         * 
         * @param seconds 
         */
        void show_page(time_t* seconds){
            lcd.clear();
            check_on();
            // header
            lcd.drawSprite(WIDTH-LEN(right_arrow[0]), 0, LEN(right_arrow), LEN(right_arrow[0]), (int *)right_arrow);
            lcd.drawSprite(0.5*WIDTH-0.5*LEN(home_icon[0]), 0, LEN(home_icon), LEN(home_icon[0]), (int *)home_icon);

            // Date and time
            char date[9];
            char time[9];
            strftime(time, 9, "%I:%M %p", localtime(seconds));
            strftime(date, 9, "%d/%m/%y", localtime(seconds));
            lcd.printString(time, SP*2, 1);
            lcd.printString(date, SP*2, 2);
            // box[0,0]
            lcd.drawRect(0, SP*7, 0.65*WIDTH, 0.4*HEIGHT-2*SP, FILL_TRANSPARENT);

            // Tempreatures
            char temp[6];
            sprintf(temp,"%.0f C",ac_temp);
            lcd.printString(temp,0.65*WIDTH+3*SP,1);
            sprintf(temp,"%.0f C",actual_temp);
            lcd.printString(temp,0.65*WIDTH+3*SP,2);
            // box[1,0]         
            lcd.drawRect(0.65*WIDTH+SP, SP*7, WIDTH-(0.65*WIDTH), 0.4*HEIGHT-2*SP, FILL_TRANSPARENT);

            // flags
            lcd.drawSprite(0, 0.4*HEIGHT-2*SP+SP*7, LEN(light_icon), LEN(light_icon[0]), (int *)light_icon);
            if(auto_light){
                lcd.drawSprite(LEN(light_icon[0])+SP, 0.4*HEIGHT-2*SP+SP*7, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            }
            else{
                lcd.drawSprite(LEN(light_icon[0])+SP, 0.4*HEIGHT-2*SP+SP*7, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
            }
            lcd.drawSprite(WIDTH-(LEN(lock_icon[0])+LEN(correct_icon[0])+3*SP), 0.4*HEIGHT-2*SP+SP*7, LEN(lock_icon), LEN(lock_icon[0]), (int *)lock_icon);
            if(security_mode){
                lcd.drawSprite(WIDTH-(LEN(lock_icon[0])+SP), 0.4*HEIGHT-2*SP+SP*7, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            }
            else{
                lcd.drawSprite(WIDTH-(LEN(lock_icon[0])+SP), 0.4*HEIGHT-2*SP+SP*7, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
            }
            lcd.drawSprite(0.5*WIDTH-(LEN(ac_icon[0])+2*SP), 0.4*HEIGHT-2*SP+SP*7, LEN(ac_icon), LEN(ac_icon[0]), (int *)ac_icon);
            if(auto_ac){
                lcd.drawSprite(0.5*WIDTH-0.5*LEN(home_icon[0])+3*SP, 0.4*HEIGHT-2*SP+SP*7, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            }
            else{
                lcd.drawSprite(0.5*WIDTH-0.5*LEN(home_icon[0])+3*SP, 0.4*HEIGHT-2*SP+SP*7, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
            }

            // Devices and appliances 
            char nd_np[9];
            sprintf(nd_np,"D:%i  A:%i", (int) devices.size(), (int) appliances.size());
            lcd.printString(nd_np, SP*2, 4);
            sprintf(nd_np,"%i    %i",operating_devices, operating_appliances);
            lcd.printString(nd_np, SP*2, 5);
            // logos
            lcd.drawCircle(15+SP, HEIGHT-(4+SP), 3, FILL_TRANSPARENT);
            lcd.drawLine(15+SP, HEIGHT-(4+SP+3), 15+SP, HEIGHT-(4+SP), FILL_BLACK);
            lcd.drawCircle(45+SP, HEIGHT-(4+SP), 3, FILL_TRANSPARENT);
            lcd.drawLine(45+SP, HEIGHT-(4+SP+3), 45+SP, HEIGHT-(4+SP), FILL_BLACK);
            // bpx[0,1]
            lcd.drawRect(0, 0.65*HEIGHT, 0.65*WIDTH, HEIGHT-(0.65*HEIGHT)+SP, FILL_TRANSPARENT);

            // On lights
            char buff_lights[5];
            sprintf(buff_lights,"L:%i",(int) lights.size());
            lcd.printString(buff_lights,0.65*WIDTH+3*SP,4);
            sprintf(buff_lights,"%i",operating_lights);
            lcd.printString(buff_lights,0.65*WIDTH+3*SP,5);
            // logos
            lcd.drawCircle(0.65*WIDTH+15+2*SP, HEIGHT-(4+SP), 3, FILL_TRANSPARENT);
            lcd.drawLine(0.65*WIDTH+15+2*SP, HEIGHT-(4+SP+3), 0.65*WIDTH+15+2*SP, HEIGHT-(4+SP), FILL_BLACK);
            // box[1,1]
            lcd.drawRect(0.65*WIDTH+SP, 0.65*HEIGHT, WIDTH-(0.65*WIDTH), HEIGHT-(0.65*HEIGHT)+SP, FILL_TRANSPARENT);
        }

};
