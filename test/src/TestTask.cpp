#include <QTimer>
#include <QSignalSpy>

#include <gtest/gtest.h>
#include <entities/Task.h>
#include "SimpleTask.h"

namespace NX_SOFTWARE_CENTER_TESTS {
class TestTask : public testing::Test {
    void SetUp()
    {
        qRegisterMetaType<Task::State>("Task::State");
    }
};

TEST_F(TestTask, successfullTask)
{
    auto t = new SimpleTask();

    QSignalSpy spy(t, &Task::stateChanged);
    t->tryStart();
    ASSERT_EQ(Task::RUNNING, t->getState());
    t->setCompleteResult();

    spy.wait(4);

    ASSERT_EQ(Task::COMPLETED, t->getState());
    ASSERT_EQ(2, spy.count());
    delete t;
}

TEST_F(TestTask, failedTask)
{
    auto t = new SimpleTask();

    QSignalSpy spy(t, &Task::stateChanged);
    t->tryStart();
    ASSERT_EQ(Task::RUNNING, t->getState());
    t->setFailResult();

    spy.wait(4);
    ASSERT_EQ(Task::FAILED, t->getState());
    ASSERT_EQ(2, spy.count());
    delete t;
}

TEST_F(TestTask, stopeddTask)
{
    auto t = new SimpleTask();

    QSignalSpy spy(t, &Task::stateChanged);
    t->tryStart();
    ASSERT_EQ(Task::RUNNING, t->getState());
    t->tryStop();
    t->checkStoppped();

    spy.wait(4);
    ASSERT_EQ(Task::STOPPED, t->getState());
    ASSERT_EQ(2, spy.count());
    delete t;
}

TEST_F(TestTask, progress)
{
    auto t = new SimpleTask();

    QSignalSpy spyProgress(t, &Task::progressValueChanged);
    t->tryStart();

    ASSERT_EQ(Task::RUNNING, t->getState());
    t->setCompleteResult();

    spyProgress.wait(2);
    ASSERT_EQ(Task::COMPLETED, t->getState());
    ASSERT_EQ(2, spyProgress.count());
    delete t;
}

}
