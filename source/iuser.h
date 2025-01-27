#ifndef IUSER_H
#define IUSER_H

#include "itasker.h"
#include "ischeduler.h"

class iuser
{
public:
    virtual const itasker &get_tasker() const noexcept = 0;
    virtual const ischeduler &get_scheduler() const noexcept = 0;
    virtual const string &get_name() const noexcept = 0;
};

#endif //IUSER_H