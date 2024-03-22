import QtQuick 2.3

Flickable {
    id:             root
    boundsBehavior: Flickable.StopAtBounds
    clip:           true

    property color indicatorColor: "black"

    Component.onCompleted: {
        var indicatorComponent = Qt.createComponent("ECSFlickableVerticalIndicator.qml")
        indicatorComponent.createObject(root)
        indicatorComponent = Qt.createComponent("ECSFlickableHorizontalIndicator.qml")
        indicatorComponent.createObject(root)
    }
}
