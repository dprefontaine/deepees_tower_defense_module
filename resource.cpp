#include "resource.h"

resource::resource(int starting_resource_amount, int max_resource){
    current_resource = starting_resource_amount;
    resource::max_resource = max_resource;
}

resource::~resource(){

}

bool resource::add_to_resource(int adding_amount){
    if (current_resource < max_resource){
        current_resource+= adding_amount;

        if (current_resource > max_resource)
            current_resource = max_resource;

        return true;
    } else {
        return false;
    }
}

bool resource::use_resource(int subbing_amount){
    if ((current_resource - subbing_amount) >= 0){
        current_resource-= subbing_amount;

        return true;
    } else {
        return false;
    }
}

int resource::get_resource(){
    return current_resource;
}
