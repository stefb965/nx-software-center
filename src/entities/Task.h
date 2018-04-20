#ifndef NX_SOFTWARE_CENTER_TASK_H
#define NX_SOFTWARE_CENTER_TASK_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QMutex>

class Task : public QObject {
Q_OBJECT
    bool stopRequested;
    int progressValue;
    int progressTotal;

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

    int getProgressValue() const;
    int getProgressTotal() const;

public slots:
    void tryStart();
    void tryStop();

protected:
    virtual void taskImpl() = 0;

    void setState(State newState);
    bool isStopRequested();

    void setProgressValue(int progressValue);
    void setProgressTotal(int progressTotal);

signals:
    void stateChanged(Task::State state);
    void progressValueChanged(int value);
    void progressTotalChanged(int value);

private:
    State state;
    Q_PROPERTY(State state MEMBER state NOTIFY stateChanged)
    Q_PROPERTY(int progressValue MEMBER progressValue NOTIFY progressValueChanged)
    Q_PROPERTY(int progressTotal MEMBER progressTotal NOTIFY progressTotalChanged)
};

Q_DECLARE_METATYPE(Task::State);

#endif //NX_SOFTWARE_CENTER_TASK_H
