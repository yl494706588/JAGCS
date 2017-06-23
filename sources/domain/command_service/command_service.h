#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class Command;

    class CommandService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandService(QObject* parent = nullptr);
        ~CommandService() override;

    public slots:
        void executeCommand(const Command& command);

    signals:
        void gotCommand();

        void download(db::MissionAssignmentPtr assignment);
        void upload(db::MissionAssignmentPtr assignment);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_SERVICE_H
