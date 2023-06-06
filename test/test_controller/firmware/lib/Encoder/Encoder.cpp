#include "Encoder.h"
#include "base_config.h"
#include "Arduino.h"

Encoder::Encoder(
    volatile long motor1_encoder_pos,
    volatile long motor2_encoder_pos,
    volatile long motor3_encoder_pos,
    volatile long motor4_encoder_pos):
    motor1_encoder_pos_(motor1_encoder_pos),
    motor2_encoder_pos_(motor2_encoder_pos),
    motor3_encoder_pos_(motor3_encoder_pos),
    motor4_encoder_pos_(motor4_encoder_pos)
    {
    }

Encoder::ticks Encoder::getTicks(unsigned long currentMillis)
{
    Encoder::ticks enc;
    enc = getTicks((unsigned long) currentMillis);
    currentMillis = millis();

    if(currentMillis - previousMillis >= 1000)
    {
        previousMillis = currentMillis;

        enc.motor1_encoder = encoder1_pos - encoder1_prev;
        enc.motor2_encoder = encoder2_pos - encoder2_prev;
        enc.motor3_encoder = encoder3_pos - encoder3_prev;
        enc.motor4_encoder = encoder4_pos - encoder4_prev;


        encoder1_prev = encoder1_pos;
        encoder2_prev = encoder2_pos;
        encoder3_prev = encoder3_pos;
        encoder4_prev = encoder4_pos;
    }

    return enc;
}