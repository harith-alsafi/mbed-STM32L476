#pragma once
#include "Variables.hpp"


/**
 * @brief Speaker class
 * 
 */
class Speaker
{
    private:
        /**
         * @brief Stores required notes
         * 
         */
        int notes[3] = {100, 200, 400};

        /**
         * @brief Plays note frequency 
         * 
         * @param frequency 
         */
        void play_note(int frequency){
        buzzer.period_us((float) 1000000.0f/ (float) frequency);   
        buzzer.pulsewidth_us(buzzer.read_period_us()/2);   
        ThisThread::sleep_for(5ms);                                     
    }

    public:

        /**
         * @brief Starts the alarm
         * 
         */
        void start_alarm(){
            for(int i = 0; i < 3; i++){
                play_note(notes[i]);
            }
        }

        /**
         * @brief Stops the alarm 
         * 
         */
        void stop_alarm(){
            buzzer.write(0);
        }

};