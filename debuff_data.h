#ifndef DEBUFF_DATA_H_INCLUDED
#define DEBUFF_DATA_H_INCLUDED

enum DEBUFF_TYPE{
    DEBUFF_MAX_HP,
    DEBUFF_REGEN,
    DEBUFF_SPEED,
    DEBUFF_ARMOR
};

struct debuff_data{
public:
    debuff_data(unsigned int threshold, int debuff_degree, DEBUFF_TYPE stat_to_debuff){
        debuff_alarm = alarm(threshold);
        degree = debuff_degree;
        debuff_stat = stat_to_debuff;
    };

    ~debuff_data(){};

    bool has_expired(unsigned int ticks){
        return debuff_alarm.alarm_set(ticks) > 0;
    };

    void reset_ticks(){
        debuff_alarm.reset_ticks();
    };

    int degree = 0;
    DEBUFF_TYPE debuff_stat = DEBUFF_SPEED;

    std::string debuff_name = "";
    std::string debuff_image = "";

private:
    alarm debuff_alarm = alarm(1000);
};


#endif // DEBUFF_DATA_H_INCLUDED
