#include "Task.h"
#include "../interactors/TaskMetadata.h"

Task::Task()
        :stopRequested(false), progressValue(-1), progressTotal(-1), state(READY)
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
int Task::getProgressValue() const
{
    return progressValue;
}
int Task::getProgressTotal() const
{
    return progressTotal;
}

void Task::setProgressValue(int progressValue)
{
    Task::progressValue = progressValue;
    emit progressValueChanged(progressValue);
}

void Task::setProgressTotal(int progressTotal)
{
    Task::progressTotal = progressTotal;
    emit progressTotalChanged(progressValue);
}
