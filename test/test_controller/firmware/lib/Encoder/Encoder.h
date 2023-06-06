#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder
{
    public:
        struct ticks
        {
            float motor1_encoder;
            float motor2_encoder;
            float motor3_encoder;
            float motor4_encoder;
        };
        
        Encoder(
            volatile long motor1_encoder_pos,
            volatile long motor2_encoder_pos,
            volatile long motor3_encoder_pos,
            volatile long motor4_encoder_pos
            );
            
        ticks getTicks(unsigned long currentMillis);

    private:
        volatile long motor1_encoder_pos_;
        volatile long motor2_encoder_pos_;
        volatile long motor3_encoder_pos_;
        volatile long motor4_encoder_pos_; 

        float encoder1_diff;
        float encoder2_diff;
        float encoder3_diff;
        float encoder4_diff;

        float encoder1_prev;
        float encoder2_prev;
        float encoder3_prev;
        float encoder4_prev;

        volatile long encoder1_pos;
        volatile long encoder2_pos;
        volatile long encoder3_pos;
        volatile long encoder4_pos;

        unsigned long currentMillis;
        unsigned long previousMillis;
};

#endif