#ifndef BUFF_DATA_H_INCLUDED
#define BUFF_DATA_H_INCLUDED

#include "debuff_data.h"

enum BUFF_TYPE{
    BUFF_ATTACK,
    BUFF_ATTACK_SPEED,
    BUFF_RANGE
};

struct buff_data{
public:
    buff_data(unsigned int threshold, int buff_degree, BUFF_TYPE stat_to_buff){
        buff_alarm = alarm(threshold);
        degree = buff_degree;
        buff_stat = stat_to_buff;
    };

    ~buff_data(){};

    bool has_expired(unsigned int ticks){
        return buff_alarm.alarm_set(ticks) > 0;
    };

    void reset_ticks(){
        buff_alarm.reset_ticks();
    }

    int degree = 0;
    BUFF_TYPE buff_stat = BUFF_ATTACK;

    std::string buff_name = "";
    std::string buff_image = "";

private:
    alarm buff_alarm = alarm(1000);
};

#endif // BUFF_DATA_H_INCLUDED
