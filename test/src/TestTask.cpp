#include <QTimer>
#include <QSignalSpy>

#include <gtest/gtest.h>
#include <entities/Task.h>

namespace NX_SOFTWARE_CENTER_TESTS {
class TestTask : public testing::Test {
    void SetUp()
    {
        qRegisterMetaType<Task::State>("Task::State");
    }
};

class SimpleTask : public Task {
public:
    bool resultReady;
    bool resultError;

    QTimer* t = nullptr;
    SimpleTask()
            :resultReady(false), resultError(false) { }
protected:
    void setFailResult()
    {
        resultError = true;
    }

    void setCompleteResult()
    {
        resultReady = true;
    }

protected slots:
    void taskImpl() override
    {
        t = new QTimer();
        t->setInterval(2);
        connect(t, &QTimer::timeout, [=]() {
          try {
              if (isStopRequested())
                  setState(STOPPED);

              if (resultReady)
                  setState(COMPLETED);

              if (resultError)
                  setState(FAILED);

              if (getState()!=Task::RUNNING) {
                  t->stop();
                  t->deleteLater();
              }
          }
          catch (std::exception ex) {
              std::cerr << ex.what() << std::endl;
          }

        });

        t->start();
    }

};

TEST_F(TestTask, successfullTask)
{
    auto t = new SimpleTask();

    QSignalSpy spy(t, &Task::stateChanged);
    t->tryStart();
    ASSERT_EQ(Task::RUNNING, t->getState());
    t->resultReady = true;

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
    t->resultError = true;

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

    spy.wait(4);
    ASSERT_EQ(Task::STOPPED, t->getState());
    ASSERT_EQ(2, spy.count());
    delete t;
}

//TEST_F(TestTask, asyncTask)
//{
//    auto task = new SimpleTask;
//
//    ASSERT_EQ(Task::READY, task->getState());
//    task->tryStart();
//
//    ASSERT_EQ(Task::RUNNING, task->getState());
//
//    QSignalSpy spy(task, &Task::stateChanged);
//    task->resultReady = true;
//
//    spy.wait();
//
//    ASSERT_EQ(Task::COMPLETED, task->getState());
//    ASSERT_EQ(1, spy.count());
//
//    auto mainThread = QThread::currentThread();
//    auto taskThread = task->thread();
//    ASSERT_NE(mainThread, taskThread);
//
//    task->tryStart();
//
//    delete task;
//}
}
