#ifndef NX_SOFTWARE_CENTER_TASK_H
#define NX_SOFTWARE_CENTER_TASK_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QMutex>

class Task : public QObject {
Q_OBJECT
    bool stopRequested;

public:
    enum State {
      READY,
      RUNNING,
      COMPLETED,
      FAILED,
      STOPPED
    };
    Q_ENUM(State)

    explicit Task();
    virtual ~Task();
    State getState();

public slots:
    void tryStart();
    void tryStop();

protected:
    virtual void taskImpl() = 0;

    void setState(State newState);
    bool isStopRequested();

signals:
    void stateChanged(Task::State state);

private:
    State state;
    Q_PROPERTY(State state MEMBER state NOTIFY stateChanged)
};

Q_DECLARE_METATYPE(Task::State);

#endif //NX_SOFTWARE_CENTER_TASK_H
