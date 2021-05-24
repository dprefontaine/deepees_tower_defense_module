#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

//FOR MANAGING RESOURCES IN TOWER DEFENSE

class resource{
public:
    resource(int starting_resource_amount, int max_resource);
    ~resource();

    bool add_to_resource(int adding_amount);
    bool use_resource(int subbing_amount);

    int get_resource();

private:
    int current_resource;
    int max_resource;
};

#endif // RESOURCE_H_INCLUDED
