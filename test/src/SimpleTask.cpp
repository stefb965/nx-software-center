//
// Created by alexis on 20/04/18.
//

#include "SimpleTask.h"
SimpleTask::SimpleTask() { }
void SimpleTask::setFailResult()
{
    setState(FAILED);
}
void SimpleTask::setCompleteResult()
{
    setProgressValue(1);
    setState(COMPLETED);
}
void SimpleTask::checkStoppped()
{
    if (isStopRequested())
        setState(STOPPED);
}
void SimpleTask::taskImpl()
{
    setProgressTotal(1);
    setProgressValue(0);

    setState(RUNNING);
}
