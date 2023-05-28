#include "Encoder.h"
#include "mecabot_base_config.h"
#include "Arduino.h"

Encoder::Encoder(
    volatile long motor_1_encoder_pos,
    volatile long motor_2_encoder_pos,
    volatile long motor_3_encoder_pos,
    volatile long motor_4_encoder_pos):
    motor_1_encoder_pos_(motor_1_encoder_pos),
    motor_2_encoder_pos_(motor_2_encoder_pos),
    motor_3_encoder_pos_(motor_3_encoder_pos),
    motor_4_encoder_pos_(motor_3_encoder_pos){}

Encoder::ticks Encoder::getTicks(unsigned long currentMillis)
{
    Encoder::ticks enc;
    enc = getTicks((unsigned long) currentMillis);
    currentMillis = millis();

    if(currentMillis - previousMillis >= 1000)
    {
        previousMillis = currentMillis;

        enc.motor_1_encoder = encoder_1_pos - encoder_1_prev;
        enc.motor_2_encoder = encoder_2_pos - encoder_2_prev;
        enc.motor_3_encoder = encoder_3_pos - encoder_3_prev;
        enc.motor_4_encoder = encoder_4_pos - encoder_4_prev;


        encoder_1_prev = encoder_1_pos;
        encoder_2_prev = encoder_2_pos;
        encoder_3_prev = encoder_3_pos;
        encoder_4_prev = encoder_4_pos;
    }

    return enc;
}