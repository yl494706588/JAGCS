#ifndef COMMUNICATION_SERVICE_H
#define COMMUNICATION_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "link_traits.h"
#include "link_description.h"

#include "i_communication_plugin.h"

namespace domain
{
    class SerialDeviceManager;

    class CommunicationService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommunicationService(QObject* parent = nullptr);
        ~CommunicationService() override;

        dto::LinkDescriptionPtr description(int id) const;
        dto::LinkDescriptionPtrList descriptions() const;

        void addPlugin(ICommunicationPlugin* plugin);
        void removePlugin(ICommunicationPlugin* plugin);

        QStringList availableProtocols() const;

    public slots:
        bool save(const dto::LinkDescriptionPtr& description);
        bool remove(const dto::LinkDescriptionPtr& description);

        void setLinkConnected(int descriptionId, bool connected);

    signals:
        void availableProtocolsChanged();

        void descriptionAdded(dto::LinkDescriptionPtr description);
        void descriptionRemoved(dto::LinkDescriptionPtr description);
        void descriptionChanged(dto::LinkDescriptionPtr description);
        void linkConnectedChanged(dto::LinkDescriptionPtr description, bool connected);
        void linkSent(int descriptionId);
        void linkRecv(int descriptionId);

    private slots:
        void onLinkConnectedChanged(int descriptionId, bool connected);
        void onLinkStatisticsChanged(int descriptionId,
                                     int timestamp,
                                     int bytesReceivedSec,
                                     int bytesSentSec);
        void onLinkErrored(int descriptionId, const QString& error);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMUNICATION_SERVICE_H
