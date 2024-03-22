import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2
import QtGraphicalEffects 1.0

FocusScope {
    id:     _root
    height: column.height

    property alias          color:          label.color
    property alias          text:           label.text
    property bool           checked:        true
    property bool           showSpacer:     true
    property ExclusiveGroup exclusiveGroup: null

    property real   _sectionSpacer: 10  // spacing between section headings

    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(_root)
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            _root.focus = true
            checked = !checked
        }

        ColumnLayout {
            id:             column
            anchors.left:   parent.left
            anchors.right:  parent.right

            Item {
                height:     _sectionSpacer
                width:      1
                visible:    showSpacer
            }

            Label {
                id:                 label
                Layout.fillWidth:   true
            }

            Rectangle {
                Layout.fillWidth:   true
                height:             1
                color:              "gray"
            }
        }
    }
}
