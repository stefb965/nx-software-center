//
// Created by alexis on 20/04/18.
//

#ifndef NX_SOFTWARE_CENTER_SIMPLETASK_H
#define NX_SOFTWARE_CENTER_SIMPLETASK_H

#include <entities/Task.h>

class SimpleTask : public Task {
public:
    SimpleTask();

    void setFailResult();

    void setCompleteResult();

    void checkStoppped();

protected:
    void taskImpl() override;

};

#endif //NX_SOFTWARE_CENTER_SIMPLETASK_H
