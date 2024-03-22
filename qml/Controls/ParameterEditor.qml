import QtQuick 2.15
import QtQuick.Controls  1.2
import QtQuick.Layouts   1.2
import QtQuick.Controls 2.15
import QtQuick.Dialogs   1.3

import EquitmentControl.Controllers   1.0
import EquitmentControl.FactSystem    1.0

Dialog {
    id: _root
    title: qsTr("参数设置")

    property int    _rowWidth:          10 // Dynamic adjusted at runtime
    property int    _rowHeight:         20
    property int    _valueLabelWidth:    150 // Dynamic adjusted at runtime
    property int    _nameLabelWidth:     150 // Dynamic adjusted at runtime
    property bool   _searchFilter:      searchText.text.trim() != "" || controller.showModifiedOnly
    property Fact   _editorDialogFact: Fact { }

    ParameterEditorController {
        id: controller
    }

    ExclusiveGroup { id: sectionGroup }

    contentItem:  Rectangle {
        color: "white"
        implicitHeight : 600
        implicitWidth : 1000

        Popup {
            id:             valueEditPopup
            padding:        7.5
            modal:          true
            focus:          true
            closePolicy:    Popup.NoAutoClose

            parent: Overlay.overlay

            background: Rectangle {
                width:  editorPopup.width
                height: editorPopup.height
                color:  "white"

                ParameterEditorPopup {
                    id: editorPopup
                    fact: _editorDialogFact
                }
            }

            Component.onCompleted: {
                editorPopup.popupClose.connect(onPopupClose)
            }

            function onPopupClose(yes) {
                valueEditPopup.close()
            }
        }

        Row {
            id:             header
            anchors.left:   parent.left
            anchors.right:  parent.right
            spacing:        10

            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Search:")
            }

            TextField {
                id:                 searchText
                text:               controller.searchText
                onDisplayTextChanged: controller.searchText = displayText
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        ECSFlickable {
            id :                groupScroll
            anchors.left:       parent.left
            anchors.top:        header.bottom
            anchors.bottom:     parent.bottom
            width:              150
            clip:               true
            pixelAligned:       true
            contentHeight:      groupedViewCategoryColumn.height
            flickableDirection: Flickable.VerticalFlick
            visible:            !_searchFilter

            ColumnLayout {
                id:             groupedViewCategoryColumn
                anchors.left:   parent.left
                anchors.right:  parent.right
                spacing:        3

                Repeater {
                    model: controller.categories

                    Column {
                        Layout.fillWidth:   true
                        spacing:            3

                        SectionHeader {
                            id:             categoryHeader
                            anchors.left:   parent.left
                            anchors.right:  parent.right
                            text:           " " + object.name
                            checked:        object == controller.currentCategory
                            exclusiveGroup: sectionGroup

                            onCheckedChanged: {
                                if (checked) {
                                    controller.currentCategory  = object
                                }
                            }
                        }

                        Repeater {
                            model: categoryHeader.checked ? object.groups : 0

                            Button {
                                width:          150
                                text:           object.name
                                height:         _rowHeight
                                checked:        object == controller.currentGroup
                                autoExclusive:  true

                                onClicked: {
                                    if (!checked) _rowWidth = 10
                                    checked = true
                                    controller.currentGroup = object
                                }
                            }
                        }
                    }
                }
            }
        }

        /// Parameter list
        ECSListView {
            id:                 editorListView
            anchors.leftMargin: 10
            anchors.left:       _searchFilter ? parent.left : groupScroll.right
            anchors.right:      parent.right
            anchors.top:        header.bottom
            anchors.bottom:     parent.bottom
            orientation:        ListView.Vertical
            flickableDirection: Flickable.HorizontalAndVerticalFlick
            contentWidth:       _rowWidth
            model:              controller.parameters
            cacheBuffer:        height > 0 ? height * 2 : 0
            clip:               true

            delegate: Rectangle {
                height: _rowHeight
                width:  _rowWidth
                color:  Qt.rgba(0,0,0,0)

                Row {
                    id:     factRow
                    spacing: 5
                    anchors.verticalCenter: parent.verticalCenter

                    property Fact modelFact: object

                    Label {
                        id:     nameLabel
                        width:  _nameLabelWidth
                        color:  "black"
                        text:   factRow.modelFact.name
                        clip:   true
                    }

                    Label {
                        id:     valueLabel
                        width:  _valueLabelWidth
                        color:  "black"
                        text:   factRow.modelFact.enumStrings.length === 0 ? factRow.modelFact.valueString + " " + factRow.modelFact.units : factRow.modelFact.enumStringValue
                        clip:   true
                    }

                    Label {
                        text:   factRow.modelFact.shortDescription
                    }

                    Component.onCompleted: {
                        if(_rowWidth < factRow.width + 10) {
                            _rowWidth = factRow.width + 10
                        }

                        if(valueLabel.contentWidth + 30 > _valueLabelWidth) {
                            _valueLabelWidth = valueLabel.contentWidth + 30
                        }

                        if(nameLabel.contentWidth + 30 > _nameLabelWidth) {
                            _nameLabelWidth = nameLabel.contentWidth + 30
                        }
                    }
                }

                Rectangle {
                    width:  _rowWidth
                    height: 1
                    color:  "blue"
                    opacity: 0.15
                    anchors.bottom: parent.bottom
                    anchors.left:   parent.left
                }

                Button {
                    id:                 tootipArea
                    anchors.fill:       parent
                    opacity:            0
                    z:                  0

                    ToolTip {
                        delay:      500                                     //tooltip 500ms后出现
                        visible:    tootipArea.hovered
                        text:       factRow.modelFact.longDescription
                    }

                    onClicked: {
                        if(!valueEditPopup.activeFocus) {
                            _editorDialogFact = factRow.modelFact
                            valueEditPopup.open()
                        }
                    }
                }
            }
        }
    }
}
