#pragma once
#include "HomePage.hpp"

/**
 * @brief Main Page class
 * 
 */
class MainPage
{
    private:
        /**
         * @brief Converts int to spaced string
         * 
         * @param a 
         * @return std::string 
         */
        std::string convert_int(int a){
            std::string str;
            if(a < 10){
                str = "0"+std::to_string(a);
            }
            else if(a >= 10){
                str = std::to_string(a);
            }
            return str;
        }

        /**
         * @brief Will return total number of days
         * 
         * @param month 
         * @param year 
         * @return float 
         */
        float  get_number_of_days(int month, int year){
            //leap year condition, if month is 2
            if(month == 2){
                if((year%400==0) || (year%4==0 && year%100!=0)){
                    return 29.0;
                }
                else{
                    return 28.0;
                }
            }
            //months which has 31 days
            else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8
            ||month == 10 || month==12){
                return 31.0;
            }	
            else{
                return 30.0;
            }
        } 
    public:
        /**
         * @brief Shows the page
         * 
         */
        void show_page(){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(0.5*WIDTH-0.5*LEN(main_icon[0]), 0, LEN(main_icon), LEN(main_icon[0]), (int *)main_icon);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);

            // change time 
            lcd.drawRect(0, LEN(main_icon), 0.5*WIDTH-SP, 0.5*(HEIGHT-LEN(main_icon)), FILL_TRANSPARENT);
            lcd.printString("Time", 8, 2);

            // change flags
            lcd.drawRect(0.5*WIDTH, LEN(main_icon), 0.5*WIDTH-SP, 0.5*(HEIGHT-LEN(main_icon)), FILL_TRANSPARENT);
            lcd.printString("Flags", 0.5*WIDTH+6, 2);


            // settings brightness and ac temp
            lcd.drawRect(0, 0.5*HEIGHT+4*SP, 0.5*WIDTH-SP, 0.5*HEIGHT-4*SP, FILL_TRANSPARENT);
            lcd.printString("Set", 8, 4);



            // Edit peripherals 
            lcd.drawRect(0.5*WIDTH, 0.5*HEIGHT+4*SP, 0.5*WIDTH-SP, 0.5*HEIGHT-4*SP, FILL_TRANSPARENT);
            lcd.printString("Adjust", 0.5*WIDTH+3, 4);   
        


        }

        /**
         * @brief Shows change time/date options
         * 
         * @param choice 
         */
        void show_change_time_options(int choice){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            lcd.printString("Change time", 4*SP, 2);
            lcd.printString("Change date", 4*SP, 4);

            if(choice == 0){
                lcd.drawLine(SP, LEN(left_arrow)+9, SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+9, 2*SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
            }
            else{
                lcd.drawLine(SP, LEN(left_arrow)+25, SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+25, 2*SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
            }
        }

        /**
         * @brief Shows change date option
         * 
         * @param choice 
         * @param preva 
         * @param prevb 
         * @return int 
         */
        int show_change_date(int choice, int preva, int prevb){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            int result = 0;
            // change day
            if(choice == 0){
                float r = pot.read()*get_number_of_days(preva, prevb);
                result = static_cast<int>(roundf(r));
                if(result == 0){
                    result = 1;
                }
                lcd.printString((convert_int(result)+"/"+convert_int(preva)+"/"+convert_int(prevb)).c_str(), WIDTH*0.5-30, 2);
                lcd.drawLine(WIDTH*0.5-30, LEN(left_arrow)+15+SP, WIDTH*0.5-30+10, LEN(left_arrow)+15+SP, FILL_BLACK);
            }

            // change month
            else if(choice == 1){
                float r = pot.read()*12.0;
                result = static_cast<int>(roundf(r));
                if(result == 0){
                    result = 1;
                }
                lcd.printString((convert_int(preva)+"/"+convert_int(result)+"/"+convert_int(prevb)).c_str(), WIDTH*0.5-30, 2);
                lcd.drawLine(WIDTH*0.5-13, LEN(left_arrow)+15+SP, WIDTH*0.5-13+10, LEN(left_arrow)+15+SP, FILL_BLACK);
            }

            // change year
            else if(choice == 2){
                float r = 2000.0+pot.read()*100.0;
                result = static_cast<int>(roundf(r));
                lcd.printString((convert_int(preva)+"/"+convert_int(prevb)+"/"+convert_int(result)).c_str(), WIDTH*0.5-30, 2);
                lcd.drawLine(WIDTH*0.5+5, LEN(left_arrow)+15+SP, WIDTH*0.5+5+23, LEN(left_arrow)+15+SP, FILL_BLACK);
            }

            return result;
        }

        /**
         * @brief Shows change time option
         * 
         * @param choice 
         * @param prev 
         * @return int 
         */
        int show_change_time(int choice, int prev){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            int result = 0;
            // change hours
            if(choice == 0){
                float r= pot.read()*23.0;
                result = static_cast<int>(roundf(r));
                lcd.printString((convert_int(result)+" : "+convert_int(prev)).c_str(), WIDTH*0.5-20, 2);
                lcd.drawLine(WIDTH*0.5-20, LEN(left_arrow)+15+SP, WIDTH*0.5-20+10, LEN(left_arrow)+15+SP, FILL_BLACK);
            }
            // change minutes 
            else if(choice == 1){
                float r = pot.read()*59.0;
                result = static_cast<int>(roundf(r));
                lcd.printString((convert_int(prev)+" : "+convert_int(result)).c_str(), WIDTH*0.5-20, 2);
                lcd.drawLine(WIDTH*0.5+10, LEN(left_arrow)+15+SP, WIDTH*0.5+10+10, LEN(left_arrow)+15+SP, FILL_BLACK);
            }
            return result;
        }

        /**
         * @brief Selects which change date/time option
         * 
         */
        void select_change_time(){
            lcd.drawRect(0+2*SP, LEN(main_icon)+2*SP, 0.5*WIDTH-5*SP, 0.5*(HEIGHT-LEN(main_icon))-4*SP, FILL_TRANSPARENT);
            lcd.drawRect(0+SP, LEN(main_icon)+SP, 0.5*WIDTH-3*SP, 0.5*(HEIGHT-LEN(main_icon))-2*SP, FILL_TRANSPARENT);
        }

        /**
         * @brief Shows change flags option 
         * 
         * @param choice 
         * @param preva 
         * @param prevb 
         * @return true 
         * @return false 
         */
        bool show_change_flags(int choice, bool preva, bool prevb){
            // headers
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            lcd.printString("Auto light:", 4*SP, 2);
            lcd.printString("Security:", 4*SP, 3);
            lcd.printString("Auto AC:", 4*SP, 4);
            bool flag = (pot.read()>0.5);
            // change light
            if(choice == 0){
                lcd.drawLine(SP, LEN(left_arrow)+9, SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+9, 2*SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
                // light 
                if(flag){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // security 
                if(preva){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // ac 
                if(prevb){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
            }

            // change security
            else if(choice == 1){
                lcd.drawLine(SP, LEN(left_arrow)+17, SP, LEN(left_arrow)+17+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+17, 2*SP, LEN(left_arrow)+17+SP+5, FILL_BLACK);
                // light 
                if(preva){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // security 
                if(flag){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // ac 
                if(prevb){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
            }

            // change ac
            else if(choice == 2){
                lcd.drawLine(SP, LEN(left_arrow)+25, SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+25, 2*SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
                // light 
                if(preva){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+9, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // security 
                if(prevb){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+17, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
                // ac 
                if(flag){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), LEN(left_arrow)+25, LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }
            }
            return flag;

        }

        /**
         * @brief Shows select change flags 
         * 
         */
        void select_change_flags(){
            lcd.drawRect(0.5*WIDTH+2*SP, LEN(main_icon)+2*SP, 0.5*WIDTH-5*SP, 0.5*(HEIGHT-LEN(main_icon))-4*SP, FILL_TRANSPARENT);
            lcd.drawRect(0.5*WIDTH+SP, LEN(main_icon)+SP, 0.5*WIDTH-3*SP, 0.5*(HEIGHT-LEN(main_icon))-2*SP, FILL_TRANSPARENT);
        }

        /**
         * @brief SHows change settings
         * 
         * @param choice 
         * @param prev 
         * @return float 
         */
        float show_settings(int choice, float prev){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);

            float result = 0.0;

            // change temp 
            if(choice == 0){
                result = MIN_TEMP+pot.read()*(MAX_TEMP-MIN_TEMP);
                ac_out.write((result-MIN_TEMP)/(MAX_TEMP-MIN_TEMP));
                char buff[14];
                sprintf(buff, "AC temp: %.0f", result);
                lcd.printString(buff, 4*SP, 2);
                sprintf(buff, "Screen: %.1f", prev);
                lcd.printString(buff, 4*SP, 4);
                lcd.drawLine(SP, LEN(left_arrow)+9, SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+9, 2*SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
            }

            else if(choice == 1){
                result = pot.read()*0.99;
                char buff[14];
                sprintf(buff, "AC temp: %.0f", prev);
                lcd.printString(buff, 4*SP, 2);
                sprintf(buff, "Screen: %.2f", result);
                lcd.setBrightness(result);
                lcd.printString(buff, 4*SP, 4);
                lcd.drawLine(SP, LEN(left_arrow)+25, SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+25, 2*SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
            }

            return result;
        }

        /**
         * @brief Shows select settings
         * 
         */
        void select_settings(){
            lcd.drawRect(0+2*SP, 0.5*HEIGHT+4*SP+2*SP, 0.5*WIDTH-5*SP, 0.5*HEIGHT-4*SP-4*SP, FILL_TRANSPARENT);
            lcd.drawRect(0+SP, 0.5*HEIGHT+4*SP+SP, 0.5*WIDTH-3*SP, 0.5*HEIGHT-4*SP-2*SP, FILL_TRANSPARENT);
        }

        /**
         * @brief Shows edit peripheral options
         * 
         * @param choice 
         */
        void show_edit_peripherals(int choice){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);
            lcd.printString("Devices", 4*SP, 2);
            lcd.printString("Lights", 4*SP, 3);
            lcd.printString("Appliances", 4*SP, 4);
            // edit devices 
            if(choice == 0){
                lcd.drawLine(SP, LEN(left_arrow)+9, SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+9, 2*SP, LEN(left_arrow)+9+5+SP, FILL_BLACK);
            }


            // edit lights 
            else if(choice == 1){
                lcd.drawLine(SP, LEN(left_arrow)+17, SP, LEN(left_arrow)+17+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+17, 2*SP, LEN(left_arrow)+17+SP+5, FILL_BLACK);
            }

            // edit appliances
            else if(choice == 2){
                lcd.drawLine(SP, LEN(left_arrow)+25, SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
                lcd.drawLine(2*SP, LEN(left_arrow)+25, 2*SP, LEN(left_arrow)+25+SP+5, FILL_BLACK);
            }

        }

        /**
         * @brief Shows adjusting peripherals
         * 
         * @param choice 
         * @param periph 
         * @param type 
         */
        void show_adjust_peripherals(std::vector<bool> &choice, std::vector<bool>&periph, int type){
            // Header
            lcd.drawSprite(0, 0, LEN(left_arrow), LEN(left_arrow[0]), (int *)left_arrow);
            lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+SP), 0, LEN(correct_icon), LEN(correct_icon[0]), (int *)correct_icon);

            if(type == 0){
                lcd.printString("D-n     state", 4*SP, 1);
            }
            else if(type == 1){
                lcd.printString("L-n     state", 4*SP, 1);
            }
            else if(type == 2){
                lcd.printString("A-n     state", 4*SP, 1);
            }
            lcd.drawLine(WIDTH*0.5-3*SP, LEN(correct_icon), WIDTH*0.5-3*SP, HEIGHT, FILL_BLACK);
            lcd.drawLine(0, LEN(correct_icon)+8, WIDTH, LEN(correct_icon)+8, FILL_BLACK);

            // the data
            char buff[4];
            bool flag;
            for(int i = 0; i < choice.size(); i++){
                if(type == 0){
                    sprintf(buff, "D-%i", i);
                }
                else if(type == 1){
                    sprintf(buff, "L-%i", i);
                }
                else if(type == 2){
                    sprintf(buff, "A-%i", i);
                }
                lcd.printString(buff, 4*SP, i+2);
                if(choice[i]){
                    flag = (pot.read() > 0.5);
                    lcd.drawLine(SP, (HEIGHT/BANKS)*(i+2), SP, (HEIGHT/BANKS)*(i+2)+SP+5, FILL_BLACK);
                    lcd.drawLine(2*SP, (HEIGHT/BANKS)*(i+2), 2*SP, (HEIGHT/BANKS)*(i+2)+SP+5, FILL_BLACK);
                    periph[i] = flag;
                }
                else{
                    flag = periph[i];
                }
                if(flag){
                    lcd.drawSprite(WIDTH-(LEN(correct_icon[0])+12), (HEIGHT/BANKS)*(i+2), LEN(correct_icon), 
                    LEN(correct_icon[0]), (int *)correct_icon);
                }
                else{
                    lcd.drawSprite(WIDTH-(LEN(false_icon[0])+14), (HEIGHT/BANKS)*(i+2), 
                    LEN(false_icon), LEN(false_icon[0]), (int *)false_icon);
                }

                if(type == 0){
                    devices_out[i] = flag;
                }
                else if(type == 1){
                    lights_out[i].write(flag);
                }
                else if(type == 2){
                    appliances_out[i] = flag;
                }
            }
        }

        /**
         * @brief Shows select edit peripherals
         * 
         */
        void select_edit_peripherals(){
            lcd.drawRect(0.5*WIDTH+2*SP, 0.5*HEIGHT+4*SP+2*SP, 0.5*WIDTH-5*SP, 0.5*HEIGHT-4*SP-4*SP, FILL_TRANSPARENT);
            lcd.drawRect(0.5*WIDTH+SP, 0.5*HEIGHT+4*SP+SP, 0.5*WIDTH-3*SP, 0.5*HEIGHT-4*SP-2*SP, FILL_TRANSPARENT);
        }

};