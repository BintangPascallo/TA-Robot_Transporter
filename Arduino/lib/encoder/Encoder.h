#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder
{
    public:
        struct ticks
        {
            float motor_1_encoder;
            float motor_2_encoder;
            float motor_3_encoder;
            float motor_4_encoder;
        };
        
        Encoder(
            volatile long motor_1_encoder_pos,
            volatile long motor_2_encoder_pos,
            volatile long motor_3_encoder_pos,
            volatile long motor_4_encoder_pos, 
            );
            
        ticks getTicks(unsigned long currentMillis);

    private:
        volatile long motor_1_encoder_pos_,
        volatile long motor_2_encoder_pos_,
        volatile long motor_3_encoder_pos_,
        volatile long motor_4_encoder_pos_, 

        float encoder_1_diff;
        float encoder_2_diff;
        float encoder_3_diff;
        float encoder_4_diff;

        float encoder_1_prev;
        float encoder_2_prev;
        float encoder_3_prev;
        float encoder_4_prev;

        volatile long encoder_1_pos;
        volatile long encoder_2_pos;
        volatile long encoder_3_pos;
        volatile long encoder_4_pos;

        unsigned long currentMillis;
        unsigned long previousMillis;
};

#endif