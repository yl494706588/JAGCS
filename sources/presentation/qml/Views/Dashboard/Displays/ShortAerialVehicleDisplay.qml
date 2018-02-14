import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "CommandControls" as CommandControls

import "../Vehicles"

Controls.Card {
    id: vehicleDisplay

    property AerialVehicle vehicle: AerialVehicle {}

    VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    onDeepIn: dashboard.selectVehicle(vehicleId)

    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        columnSpacing: sizings.spacing
        rowSpacing: sizings.spacing
        columns: 4

        Indicators.YawIndicator {
            id: compass
            implicitWidth: sizings.controlBaseSize * 2
            implicitHeight: width
            yaw: vehicle.ahrs.yaw
            Layout.rowSpan: 2

            Indicators.BarIndicator {
                anchors.verticalCenter: ah.verticalCenter
                anchors.right: ah.left
                width: ah.width * 0.1
                height: ah.height * 0.6
                value: vehicle.powerSystem.throttle
            }

            Indicators.ArtificialHorizon {
                id: ah
                anchors.centerIn: parent
                height: parent.height - parent.size * 2
                width: height * 0.7
                enabled: vehicle.online &&  vehicle.ahrs.enabled
                armed: vehicle.armed
                pitch: vehicle.ahrs.pitch
                roll: vehicle.ahrs.roll
                rollInverted: settings.boolValue("Gui/fdRollInverted")
            }

            Indicators.BarIndicator {
                anchors.verticalCenter: ah.verticalCenter
                anchors.left: ah.right
                width: ah.width * 0.1
                height: ah.height * 0.6
                value: vehicle.barometric.climb
                fillColor: vehicle.barometric.climb > 0 ? palette.skyColor :
                                                          palette.groundColor
                minValue: -10
                maxValue: 10 // TODO: to consts
            }
        }

        Controls.Label {
            text: vehicle.vehicleName
            font.bold: true
            wrapMode: Text.NoWrap
            Layout.alignment: Qt.AlignHCenter
            Layout.columnSpan: 3
        }

        Indicators.FdLabel {
            digits: 0
            value: vehicle.satellite.displayedGroundSpeed
            enabled: vehicle.satellite.enabled
            operational: vehicle.satellite.operational
            prefix: qsTr("GS") + ", " + vehicle.speedSuffix
        }

        Indicators.FdLabel {
            digits: 0
            value: vehicle.pitot.displayedTrueAirspeed
            enabled: vehicle.pitot.enabled
            operational: vehicle.pitot.operational
            prefix: qsTr("TAS") + ", " + vehicle.speedSuffix
        }

        Indicators.FdLabel {
            value: vehicle.barometric.displayedAltitude
            enabled: vehicle.barometric.enabled
            operational: vehicle.barometric.operational
            prefix: qsTr("ALT") + ", " + vehicle.altitudeSuffix
        }
    }
}