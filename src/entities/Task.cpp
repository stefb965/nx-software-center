#include "Task.h"
#include "../interactors/TaskMetadata.h"

Task::Task()
        :stopRequested(false), state(READY)
{
}

void Task::tryStart()
{
    if (state==READY) {
        setState(RUNNING);
        taskImpl();
    }
}

void Task::tryStop()
{
    stopRequested = true;
}

void Task::setState(Task::State newState)
{
    if (state!=newState) {
        state = newState;
        emit stateChanged(newState);
    }
}
Task::State Task::getState()
{
    return state;
}
bool Task::isStopRequested()
{
    return stopRequested;
}
Task::~Task()
{
}
