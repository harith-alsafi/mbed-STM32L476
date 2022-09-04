#pragma once
#include "MainPage.hpp"
#include <cstdio>

/**
 * @brief Control class that manipulates everything 
 * 
 */
class Control
{  
    private:
        /**
         * @brief LDR value
         * 
         */
        float ldr_val;

        /**
         * @brief Tempreature value
         * 
         */
        float tmp_val;

        /**
         * @brief Force sensor value
         * 
         */
        float fsr_val;

        /**
         * @brief Stores the main brightness of screen
         * 
         */
        float main_brightness;

        /**
         * @brief Speaker object
         * 
         */
        Speaker speaker;

        /**
         * @brief Used to keep track of time 
         * 
         */
        time_t seconds;

        /**
         * @brief HomePage object
         * 
         */
        HomePage home_page;

        /**
         * @brief MainPage Object
         * 
         */
        MainPage main_page;

        /**
         * @brief State enum 
         * 
         */
        State STATE;

        /**
         * @brief Used in main page selection
         * 
         */
        bool left_side;

        /**
         * @brief Used in main page selection 
         * 
         */
        bool down_side;

        /**
         * @brief Options enum
         * 
         */
        Options OPTION;

        /**
         * @brief Reads sensor values 
         * 
         */
        void read_sensors(){
            ldr_val = ldr_sensor.read();
            if(abs(tmp_val-(tmp_sensor.read()*1500.0)/10.0) >= 1.25){
                tmp_val = (tmp_sensor.read()*1500.0)/10.0;
            }
            fsr_val = fsr_sensor.read();
            home_page.set_actual_temp(round(tmp_val));
        }

        /**
         * @brief Set the MainPage object
         * 
         */
        void set_main(){
            main_page.select_change_time(); // selected by default 
            left_side = true;
            down_side = false;
            OPTION = CHANGE_TIME;
        }

        /**
         * @brief Called at start of each loop
         * 
         */
        void start_loop(){
            read_sensors();
            seconds = time(NULL);
            if(home_page.get_security_mode()){
                if(fsr_val > 0.5){
                    STATE = SECURITY;
                }
            }
            if(home_page.get_auto_light()){
                for(int i = 0; i < N_LIGHTS; i++){
                    if(lights_out[i].read() > 0.00){
                        lights_out[i].write(
                            ((1.0-ldr_val) <= 0.05) ?
                            0.01 : (1.0-ldr_val)
                        );
                    }
                }
            }
            if(home_page.get_auto_ac()){
                if(tmp_val >= 20.0){
                    home_page.set_ac_temp(tmp_val-2.0);
                }
                else{
                    home_page.set_ac_temp(tmp_val+2.0);
                }
            }
        }

        /**
         * @brief Checks main page selections
         * 
         */
        void check_main_selection(){
            // change time 
            // [up, right] ---WEST--> [up,left]
            if(!down_side && !left_side && joystick.get_direction() == W){
                lcd.clear();
                main_page.show_page();
                main_page.select_change_time();
                left_side = true;
                OPTION = CHANGE_TIME;
            }
            // [down, left] --NORTH--> [up,left]
            if(down_side && left_side && joystick.get_direction() == N){
                lcd.clear();
                main_page.show_page();
                main_page.select_change_time();
                down_side = false;
                OPTION = CHANGE_TIME;
            }

            // change flags 
            // [up, left] --EAST--> [up, right]
            if(!down_side && left_side && joystick.get_direction() == E){
                lcd.clear();
                main_page.show_page();
                main_page.select_change_flags();
                left_side = false;
                OPTION = CHANGE_FLAG;
            }
            // [down, right] --NORTH--> [up, right]
            if(down_side && !left_side && joystick.get_direction() == N){
                lcd.clear();
                main_page.show_page();
                main_page.select_change_flags();
                down_side = false;
                OPTION = CHANGE_FLAG;
            }

            // settings brightness and ac temp 
            // [down, right] --WEST--> [down, left]
            if(down_side && !left_side && joystick.get_direction() == W){
                lcd.clear();
                main_page.show_page();
                main_page.select_settings();
                left_side = true;
                OPTION = SETTINGS;
            }
            // [up, left] --SOUTH--> [down, left]
            if(!down_side && left_side && joystick.get_direction() == S){
                lcd.clear();
                main_page.show_page();
                main_page.select_settings();
                down_side = true;
                OPTION = SETTINGS;
            }

            // edit peripherals
            // [down, left] --EAST--> [down, right]
            if(down_side && left_side && joystick.get_direction() == E){
                lcd.clear();
                main_page.show_page();
                main_page.select_edit_peripherals();
                left_side = false;
                OPTION = EDIT_PERIPHERALS;
            }
            // [up, right] --SOUTH--> [down, right]
            if(!down_side && !left_side && joystick.get_direction() == S){
                lcd.clear();
                main_page.show_page();
                main_page.select_edit_peripherals();
                down_side = true;
                OPTION = EDIT_PERIPHERALS;
            }
        }

        /**
         * @brief Runs change the time option of MainPage
         * 
         */
        void run_change_time(){
            int choice = 0;
            bool chosen = false;
            int hour = home_page.get_hour();
            int min = home_page.get_minute();
            int day = home_page.get_day();
            int month = home_page.get_month();
            int year = home_page.get_year();
            int time_choice = 0;
            int date_choice = 0;
            while(OPTION == CHANGE_TIME)
            {
                start_loop();
                if(STATE == SECURITY){
                    break;
                }
                if(joystick.get_direction() == N){
                    choice = 0;
                }
                if(joystick.get_direction() == S){
                    choice = 1;
                }

                // change time 
                while(choice == 0 && chosen)
                {
                    start_loop();
                    if(STATE == SECURITY){
                        break;
                    }
                    if(joystick.get_direction() == W){
                        time_choice = 0;
                    }
                    else if(joystick.get_direction() == E){
                        time_choice = 1;                            
                    }
                    if(time_choice == 0){
                        lcd.clear();
                        hour = main_page.show_change_time(time_choice, min);
                    }
                    if(time_choice == 1){
                        lcd.clear();
                        min = main_page.show_change_time(time_choice, hour);
                    }

                    // go back 
                    if(left_button.read() == 1){
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 0;
                        chosen = false;

                    }
                    // click ok
                    if(right_button.read() == 1){
                        home_page.set_time_only(hour, min);
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 0;
                        chosen = false;
                    }
                    lcd.refresh();
                }

                // change date
                while(choice == 1 && chosen)
                {
                    start_loop();
                    if(STATE == SECURITY){
                        break;
                    }
                    if(joystick.get_direction() == E && date_choice == 0){
                        date_choice = 1;
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    else if(joystick.get_direction() == E && date_choice == 1){
                        date_choice = 2;
                        ThisThread::sleep_for(WAIT+25ms);

                    }

                    else if(joystick.get_direction() == W && date_choice == 2){
                        date_choice = 1;
                        ThisThread::sleep_for(WAIT+50ms);

                    }

                    else if(joystick.get_direction() == W && date_choice == 1){
                        date_choice = 0;
                        ThisThread::sleep_for(WAIT+25ms);
                    }

                    // chnage day
                    if(date_choice == 0){
                        lcd.clear();
                        day = main_page.show_change_date(date_choice, month, year);
                    }

                    // change month 
                    if(date_choice == 1){
                        lcd.clear();
                        month = main_page.show_change_date(date_choice, day, year);
                    }      

                    // change year
                    if(date_choice == 2){
                        lcd.clear();
                        year = main_page.show_change_date(date_choice, day, month);
                    }     

                    // go back 
                    if(left_button.read() == 1){
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 1;
                        chosen = false;

                    }
                    // click ok
                    if(right_button.read() == 1){
                        home_page.set_date_only(day, month, year);
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 1;
                        chosen = false;
                    }
                    lcd.refresh();
                }
                
                // show the choices
                lcd.clear();
                main_page.show_change_time_options(choice);
                
                // go back to main page 
                if(left_button.read() == 1){
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }

                // chose the selected option 
                if(right_button.read() == 1){
                    ThisThread::sleep_for(WAIT);
                    chosen = true;
                }

                lcd.refresh();
            }
        }

        /**
         * @brief Runs change flags option of MainPage
         * 
         */
        void run_change_flags(){
            int choice = 0;
            bool auto_light = home_page.get_auto_light();
            bool security_mode = home_page.get_security_mode();
            bool auto_ac = home_page.get_auto_ac();

            while(OPTION == CHANGE_FLAG)
            {
                start_loop();
                if(STATE == SECURITY){
                    break;
                }
                if(joystick.get_direction() == S && choice == 0){
                    choice = 1;
                    ThisThread::sleep_for(WAIT+50ms);
                }

                else if(joystick.get_direction() == S && choice == 1){
                    choice = 2;
                    ThisThread::sleep_for(WAIT+25ms);
                }

                else if(joystick.get_direction() == N && choice == 2){
                    choice = 1;
                    ThisThread::sleep_for(WAIT+50ms);
                }

                else if(joystick.get_direction() == N && choice == 1){
                    choice = 0;
                    ThisThread::sleep_for(WAIT+25ms);
                }

                // change light
                if(choice == 0){
                    lcd.clear();
                    auto_light = main_page.show_change_flags(choice, security_mode, auto_ac);
                }

                // change security 
                if(choice == 1){
                    lcd.clear();
                    security_mode = main_page.show_change_flags(choice, auto_light, auto_ac);
                }

                // change ac
                if(choice == 2){
                    lcd.clear();
                    auto_ac = main_page.show_change_flags(choice, auto_light, security_mode);
                }

                // chosen 
                if(right_button.read() == 1){
                    home_page.set_auto_light(auto_light);
                    home_page.set_auto_ac(auto_ac);
                    home_page.set_security_mode(security_mode);
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }

                // go back to main page 
                if(left_button.read() == 1){
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }
                lcd.refresh();
            }
        }
        
        /**
         * @brief Runs setting option of MainPage
         * 
         */
        void run_settings(){
            int choice = 0;
            float temp = home_page.get_temp();
            float brightness = 0.5;
            while(OPTION == SETTINGS)
            {
                start_loop();
                if(STATE == SECURITY){
                    break;
                }
                if(joystick.get_direction() == S){
                    choice = 1;
                }
                else if(joystick.get_direction() == N){
                    choice = 0;
                }

                // change temp
                if(choice == 0){
                    lcd.clear();
                    temp = main_page.show_settings(choice, brightness);
                }

                // change brightness
                if(choice == 1){
                    lcd.clear();
                    brightness = main_page.show_settings(choice, temp);
                }

                // chosen 
                if(right_button.read() == 1){
                    main_brightness = brightness;
                    home_page.set_ac_temp(temp);
                    home_page.set_auto_ac(false);
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }

                // go back to main page 
                if(left_button.read() == 1){
                    home_page.reset_ac();
                    lcd.setBrightness(main_brightness);
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }
                lcd.refresh();
            }
        }

        /**
         * @brief Runs edit peripherals option of MainPage
         * 
         */
        void run_edit_peripherals(){
            int choice = 0;
            bool chosen = false;
            std::vector<bool> devices = home_page.get_devices();
            std::vector<bool> lights = home_page.get_lights();
            std::vector<bool> appliances = home_page.get_appliances();
            std::vector<bool> device_choices(devices.size(), false);
            std::vector<bool> light_choices(lights.size(), false);
            std::vector<bool> appliances_choices(appliances.size(), false);
            device_choices[0] = true;
            light_choices[0] = true;
            appliances_choices[0] = true;
            
            auto get_index = [&](std::vector<bool> &a)->int{
                for(int i = 0; i < a.size(); i++){
                    if(a[i]){
                        return i;
                    }
                }
                return -1;
            };

            auto increment = [&](std::vector<bool> &a)->void{
                int i = get_index(a);
                if(i != -1 && i+1 < a.size()){
                    a[i] = false;
                    a[i+1] = true;
                }
            };
            
            auto decrement = [&](std::vector<bool> &a)->void{
                int i = get_index(a);
                if(i != -1 && i-1 >= 0){
                    a[i] = false;
                    a[i-1] = true;
                }    
            };

            while(OPTION == EDIT_PERIPHERALS)
            {
                start_loop();
                if(STATE == SECURITY){
                    break;
                }
                if(joystick.get_direction() == S && choice == 0){
                    choice = 1;
                    ThisThread::sleep_for(WAIT+50ms);
                }

                else if(joystick.get_direction() == S && choice == 1){
                    choice = 2;
                    ThisThread::sleep_for(WAIT+25ms);
                }

                else if(joystick.get_direction() == N && choice == 2){
                    choice = 1;
                    ThisThread::sleep_for(WAIT+50ms);
                }

                else if(joystick.get_direction() == N && choice == 1){
                    choice = 0;
                    ThisThread::sleep_for(WAIT+25ms);
                }

                // showing choices 
                lcd.clear();
                main_page.show_edit_peripherals(choice);

                // devices
                while(choice == 0 && chosen)
                {
                    start_loop();
                    if(STATE == SECURITY){
                        break;
                    }

                    if(joystick.get_direction() == S){
                        increment(device_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    if(joystick.get_direction() == N){
                        decrement(device_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    lcd.clear();
                    main_page.show_adjust_peripherals(device_choices, devices, choice);

                    // go back 
                    if(left_button.read() == 1){
                        home_page.reset_devices();
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 0;
                        chosen = false;

                    }
                    // click ok
                    if(right_button.read() == 1){
                        home_page.set_devices(devices);
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 0;
                        chosen = false;
                    }
                    lcd.refresh();
                }

                // lights
                while(choice == 1 && chosen)
                {
                    start_loop();
                    if(STATE == SECURITY){
                        break;
                    }

                    if(joystick.get_direction() == S){
                        increment(light_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    if(joystick.get_direction() == N){
                        decrement(light_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    lcd.clear();
                    main_page.show_adjust_peripherals(light_choices, lights, choice);

                    // go back 
                    if(left_button.read() == 1){
                        home_page.reset_lights();
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 1;
                        chosen = false;

                    }
                    // click ok
                    if(right_button.read() == 1){
                        home_page.set_lights(lights);
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 1;
                        chosen = false;
                    }
                    lcd.refresh();
                }

                // appliances
                while(choice == 2 && chosen)
                {
                    start_loop();
                    if(STATE == SECURITY){
                        break;
                    }

                    if(joystick.get_direction() == S){
                        increment(appliances_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    if(joystick.get_direction() == N){
                        decrement(appliances_choices);
                        ThisThread::sleep_for(WAIT+50ms);
                    }

                    lcd.clear();
                    main_page.show_adjust_peripherals(appliances_choices, appliances, choice);

                    // go back 
                    if(left_button.read() == 1){
                        home_page.reset_appliances();
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 2;
                        chosen = false;

                    }
                    // click ok
                    if(right_button.read() == 1){
                        home_page.set_appliances(appliances);
                        ThisThread::sleep_for(WAIT);
                        lcd.clear();
                        choice = 2;
                        chosen = false;
                    }
                    lcd.refresh();
                }

                // go back to main page 
                if(left_button.read() == 1){
                    ThisThread::sleep_for(WAIT);
                    lcd.clear();
                    set_main();
                    break;
                }

                // chose the selected option 
                if(right_button.read() == 1){
                    ThisThread::sleep_for(WAIT);
                    chosen = true;
                }
                lcd.refresh();
            }
        }

        /**
         * @brief Runs HomePage
         * 
         */
        void run_home_page(){
            while(STATE == HOME)
            {
                start_loop();
                home_page.show_page(&seconds);
                lcd.refresh();

                // Switch to standby 
                if(main_button.read() == 1){
                    STATE = STANDBY;
                    lcd.clear();
                }

                // switch to main page
                if(right_button.read() == 1){
                    STATE = MAIN;
                    lcd.clear();
                    set_main();
                }
            }
        }

        /**
         * @brief Runs MainPage
         * 
         */
        void run_main_page(){
            while(STATE == MAIN)
            {
                start_loop();
                main_page.show_page();

                check_main_selection();

                // we chose an option
                if(joystick.get_direction() == CENTRE && right_button.read() == 1){
                    ThisThread::sleep_for(WAIT+50ms);
                    lcd.clear();

                    // chnage time
                    run_change_time();
                
                    // change flags 
                    run_change_flags();

                    // brightness and ac temp
                    run_settings();

                    // edit peripherals
                    run_edit_peripherals();

                }

                lcd.refresh();

                // switch to home page
                if(left_button.read() == 1){
                    STATE = HOME;
                    lcd.clear();
                }

                // Switch to standby 
                if(main_button.read() == 1){
                    STATE = STANDBY;
                    lcd.clear();
                }
            }
        }

        /**
         * @brief Runs Standby Page
         * 
         */
        void run_standby_page(){
            if(STATE == STANDBY){
                lcd.setBrightness(0.01);
                lcd.clear();
            }
            while(STATE == STANDBY)
            {
                start_loop();
                lcd.printString("STAND-BY", 18, 2);
               
                lcd.refresh();
                // bach to home
                if(main_button.read() == 1){
                    STATE = HOME;
                    lcd.clear();
                    lcd.setBrightness(main_brightness);
                }
            }
        }

        /**
         * @brief Runs security mode
         * 
         */
        void run_security_page(){
            if(STATE == SECURITY){
                lcd.clear();
            }
            while(STATE == SECURITY)
            {
                seconds = time(NULL);
                lcd.printString("WARNING: ALARM", 1, 2);

                if(left_button.read() == 1 && right_button.read() == 1 && main_button.read() == 1){
                    lcd.clear();
                    STATE = HOME;
                    speaker.stop_alarm();
                    lcd.printString("PENDING", 1, 2);
                    lcd.refresh();
                    ThisThread::sleep_for(WAIT+WAIT+WAIT);
                    lcd.clear();
                    break;
                }   
                speaker.start_alarm();
                ThisThread::sleep_for(WAIT);
                lcd.refresh();
            }
        }

    public:
        /**
         * @brief Construct a new Control object
         * 
         */
        Control(){
            joystick.init();
            lcd.init(LPH7366_1);        
            lcd.setContrast(0.55);   
            main_brightness = 0.5;   
            lcd.setBrightness(0.5);     
            ldr_val = 0.0;
            tmp_val = 0.0;
            fsr_val = 0.0;
            left_button.mode(PullNone);  
            right_button.mode(PullNone); 
            main_button.mode(PullNone); 
            STATE = HOME;
            home_page.set_time_date(2, 10, 23, 11, 2022);
            devices_out = 0b00;
            appliances_out = 0b000;
            for(int i = 0; i < N_LIGHTS; i++){
                lights_out[i].write(0.0);
            }
            ac_out.write(0.95);
        }

        /**
         * @brief Runs everything
         * 
         */
        void run(){
            lcd.clear();
            start_loop();
            
            // Home state
            run_home_page();
            ThisThread::sleep_for(WAIT+25ms);

            // Main page
            run_main_page();
            ThisThread::sleep_for(WAIT+25ms);

            // Standby state
            run_standby_page();
            ThisThread::sleep_for(WAIT+25ms);

            // alarm security page
            run_security_page();
            ThisThread::sleep_for(WAIT+25ms);

            lcd.refresh();
        }
};