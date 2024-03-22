import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts  1.2

import EquitmentControl.FactSystem    1.0

Item {
    width: 600
    height: 300

    property Fact   fact
    property bool   _allowDefaultReset:   fact.defaultValueAvailable

    signal popupClose(bool yes)

    function bitmaskValue() {
        var value = 0;
        for (var i = 0; i < fact.bitmaskValues.length; ++i) {
            var checkbox = bitmaskRepeater.itemAt(i)
            if (checkbox.checked) {
                value |= fact.bitmaskValues[i];
            }
        }
        return value
    }

    function accept() {
        validationError.text = ""
        if (bitmaskColumn.visible) {
            fact.value = bitmaskValue();
            fact.valueChanged(fact.value)
            popupClose(true);
        } else if (factCombo.visible) {
            fact.enumIndex = factCombo.currentIndex
            popupClose(true);
        } else {
            var errorString = fact.validate(valueField.text, false)
            if (errorString === "") {
                fact.value = valueField.text
                fact.valueChanged(fact.value)
                popupClose(true);
            } else {
                console.log(errorString)
                validationError.text = errorString
            }
        }
    }

    function reject() {
        validationError.text = ""
        fact.valueChanged(fact.value)
        popupClose(false);
    }

    ECSFlickable {
        id:                 flickable
        anchors.fill:       parent
        contentHeight:      _column.y + _column.height
        flickableDirection: Flickable.VerticalFlick

        Column {
            id:             _column
            spacing:        10
            anchors.left:   parent.left
            anchors.right:  parent.right
            anchors.top:    parent.top
            anchors.leftMargin: 10
            anchors.topMargin: 10
            anchors.rightMargin: 10

            Label {
                id:         validationError
                width:      parent.width
                wrapMode:   Text.WordWrap
                color:      "red"
            }

            Label {
                text:       qsTr("Parameter name: ") + fact.name
                visible:    fact.componentId > 0 // > 0 means it's a parameter fact
            }

            RowLayout {
                spacing:        20
                anchors.left:   parent.left
                anchors.right:  parent.right

                TextField {
                    id:                 valueField
                    text:               fact.valueString
                    visible:            fact.enumStrings.length === 0
                    Layout.fillWidth:   true
                    focus:              true
                    implicitHeight:     40
                    activeFocusOnPress: true
                    antialiasing:       true
                }

                Button {
                    visible:    _allowDefaultReset
                    text:       qsTr("Reset to default")

                    onClicked: {
                        fact.value = fact.defaultValue
                        fact.valueChanged(fact.value)
                        popupClose(true);
                    }
                }
            }

            ComboBox {
                id:             factCombo
                anchors.left:   parent.left
                anchors.right:  parent.right
                visible:        _showCombo
                model:          fact.enumStrings

                property bool _showCombo: fact.enumStrings.length !== 0 && fact.bitmaskStrings.length === 0

                Component.onCompleted: {
                    // We can't bind directly to fact.enumIndex since that would add an unknown value
                    // if there are no enum strings.
                    if (_showCombo) {
                        currentIndex = fact.enumIndex
                    }
                }

                onCurrentIndexChanged: {
                    if (currentIndex >=0 && currentIndex < model.length) {
                        valueField.text = fact.enumValues[currentIndex]
                    }
                }
            }

            Column {
                id:         bitmaskColumn
                spacing:    15
                visible:    fact.bitmaskStrings.length > 0 ? true : false;

                Repeater {
                    id:     bitmaskRepeater
                    model:  fact.bitmaskStrings

                    delegate : CheckBox {
                        text : modelData
                        checked : fact.value & fact.bitmaskValues[index]

                        onClicked: {
                            valueField.text = bitmaskValue()
                        }
                    }
                }
            }

            Label {
                width:      parent.width
                wrapMode:   Text.WordWrap
                visible:    !longDescriptionLabel.visible
                text:       fact.shortDescription
            }

            Label {
                id:         longDescriptionLabel
                width:      parent.width
                wrapMode:   Text.WordWrap
                visible:    fact.longDescription != ""
                text:       fact.longDescription
            }

            Row {
                spacing: 20

                Label {
                    id:         minValueDisplay
                    text:       qsTr("Min: ") + fact.minString
                    visible:    !fact.minIsDefaultForType
                }

                Label {
                    text:       qsTr("Max: ") + fact.maxString
                    visible:    !fact.maxIsDefaultForType
                }
            }

            Row {
                id: valueEditPopupBtnRow
                spacing: 20
                Button {
                    height: 50
                    width: 100
                    text: qsTr("Save")
                    onClicked: accept()
                }
                Button {
                    height: 50
                    width: 100
                    text: qsTr("Cancel")
                    onClicked: reject()
                }
            }
        }
    }
}
