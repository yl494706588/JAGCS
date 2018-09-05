#include "link_provider.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "link_statistics.h"

#include "service_registry.h"
#include "communication_service.h"
#include "serial_ports_service.h"

namespace
{
    const QString separator = ",";
}

using namespace presentation;

class LinkProvider::Impl
{
public:
    domain::CommunicationService* const service = serviceRegistry->communicationService();
    dto::LinkDescriptionPtr description;
    dto::LinkStatisticsPtr statistics;
};

LinkProvider::LinkProvider(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(d->service, &domain::CommunicationService::availableProtocolsChanged,
            this, &LinkProvider::availableProtocolsChanged);

    connect(d->service, &domain::CommunicationService::descriptionChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (d->description == description) emit propertiesChanged();
    });

    connect(d->service, &domain::CommunicationService::linkConnectedChanged, this,
            [this](const dto::LinkDescriptionPtr& description) {
        if (d->description == description) emit connectedChanged();
    });
    connect(d->service, &domain::CommunicationService::linkStatisticsChanged, this,
            [this](const dto::LinkStatisticsPtr& statistics) {
        if (d->description && d->description->id() == statistics->linkId())

            d->statistics = statistics;
            emit statisticsChanged();
    });
    connect(d->service, &domain::CommunicationService::linkSent,
            this, [this](int descriptionId) {
        if (d->description && d->description->id() == descriptionId) emit sent();
    });
    connect(d->service, &domain::CommunicationService::linkRecv,
            this, [this](int descriptionId) {
        if (d->description && d->description->id() == descriptionId) emit recv();
    });
}

LinkProvider::~LinkProvider()
{}

dto::LinkDescriptionPtr LinkProvider::description() const
{
    return d->description;
}

QString LinkProvider::name() const
{
    return d->description ? d->description->name() : tr("None");
}

QString LinkProvider::protocol() const
{
    return d->description ? d->description->protocol() : tr("Unknown");
}

dto::LinkDescription::Type LinkProvider::type() const
{
    return d->description ? d->description->type() : dto::LinkDescription::UnknownType;
}

bool LinkProvider::isConnected() const
{
    return d->description && d->description->isConnected();
}

float LinkProvider::bytesRecv() const
{
    return d->statistics ? d->statistics->bytesRecv() : 0;
}

float LinkProvider::bytesSent() const
{
    return d->statistics ? d->statistics->bytesSent() : 0;
}

QStringList LinkProvider::availableProtocols() const
{
    QStringList protocols;

    protocols.append(QString());
    protocols.append(d->service->availableProtocols());

    if (d->description && !protocols.contains(d->description->protocol()))
    {
        protocols.append(d->description->protocol());
    }

    return protocols;
}

QVariantList LinkProvider::baudRates() const
{
    QVariantList baudRates;

    for (qint32 rate: domain::SerialPortService::availableBaudRates()) baudRates.append(rate);

    return baudRates;
}

QVariant LinkProvider::parameter(dto::LinkDescription::Parameter key) const
{
    return d->description ? d->description->parameter(key) : QVariant();
}

void LinkProvider::setDescription(const dto::LinkDescriptionPtr& description)
{
    if (d->description == description) return;

    d->description = description;

    emit propertiesChanged();
    emit connectedChanged();
    emit statisticsChanged();
}

void LinkProvider::setConnected(bool connected)
{
    if (d->description) d->service->setLinkConnected(d->description->id(), connected);
}

void LinkProvider::remove()
{
    if (d->description) d->service->remove(d->description);
}

void LinkProvider::setName(const QString& name)
{
    if (d->description.isNull()) return;

    d->description->setName(name);
    d->service->save(d->description);
}

void LinkProvider::setProtocol(const QString& protocol)
{
    if (d->description.isNull()) return;

    d->description->setProtocol(protocol);
    d->service->save(d->description);
}

void LinkProvider::setParameter(dto::LinkDescription::Parameter key, const QVariant& parameter)
{
    if (d->description.isNull()) return;
    
    d->description->setParameter(key, parameter);
    d->service->save(d->description);
}
