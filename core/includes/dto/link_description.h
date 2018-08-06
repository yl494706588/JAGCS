#ifndef LINK_DESCRIPTION_H
#define LINK_DESCRIPTION_H

// Internal
#include "base_dto.h"

// Qt
#include <QVariant>
#include <QMap>

namespace dto
{
    class LinkDescription: public BaseDto
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)
        Q_PROPERTY(QString parameters READ parameters WRITE setParameters)
        Q_PROPERTY(bool autoConnect READ isAutoConnect WRITE setAutoConnect)

    public:
        enum Type: quint8
        {
            UnknownType = 0,
            Serial,
            Udp,
            Tcp,
            Bluetooth
        };

        enum Parameter
        {
            UnknownParameter = 0,

            Device,
            BaudRate,
            Address,
            Port,
            Endpoints,
            UdpAutoResponse
        };

        QString name() const;
        void setName(const QString& name);

        Type type() const;
        void setType(Type type);

        QString parameters() const;
        void setParameters(const QString& parameters);
        QVariant parameter(Parameter key, const QVariant& parameter = QVariant());
        void setParameter(Parameter key, const QVariant& parameter);
        void clearParameters();
        void clearSuperfluousParameters();

        bool isAutoConnect() const;
        void setAutoConnect(bool autoConnect);

        QString protocol() const;
        void setProtocol(const QString& protocol);

        bool isConnected() const;
        void setConnected(bool isConnected);

    private:
        QString m_name;
        Type m_type = UnknownType;
        QMap<Parameter, QVariant> m_parameters;
        bool m_autoConnect = true;
        QString m_protocol;

        bool m_connected = false;

        Q_ENUM(Type)
        Q_ENUM(Parameter)
    };
}

#endif // LINK_DESCRIPTION_H
