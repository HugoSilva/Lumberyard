#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QThread>

#include <AzCore/Memory/SystemAllocator.h>

#pragma once

namespace AzToolsFramework
{
    //! Qt suppresses all timer events during modal dialogs, this object allows us to 
    //! emit a Tick event from which we can broadcast a SystemTick event.
    class Ticker
        : public QObject
    {
    public:
        Q_OBJECT

    public:

        Ticker(QObject* parent = nullptr, float timeoutMS = 10.f);
        virtual ~Ticker();

        //! Starts the ticking on a thread
        void Start();

        //! Cancels and destroys the ticking thread
        void Cancel();

    Q_SIGNALS:
        //! Connect to this signal to handle the tick
        void Tick();

    private Q_SLOTS:
        //! Single shot event that emits the Tick signal
        void Loop();

    private:

        QThread* m_thread;
        bool m_cancelled;
        float m_timeoutMS;
    };

}