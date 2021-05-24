#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

#include <deepees_framework.h>

class hitbox{
public:
    hitbox(int contact_id);
    ~hitbox();

    void set_contact_id(int new_id);
    int get_contact_id();

    int get_contact_hit();

protected:
    point moveback;

    int contact_id;
    int hit_id;
};

#endif // HITBOX_H_INCLUDED
