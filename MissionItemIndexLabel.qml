import QtQuick 2.15
import QtQuick.Controls 1.2
import EquitmentControl     1.0


Item {
    id:     root
    x:labelx
    y:labely

    width:  _width
    height: _height

    signal clicked(int x)
    property int labelx
    property int labely
    property string label:                  index <= 1 ? "Begin" : ""           ///< Label to show to the side of the index indicator
    property int    index:                  -1       ///< Index to show in the indicator, 0 will show single char label instead, -1 first char of label in indicator full label to the side
    property bool   checked:                true
    property bool   small:                  !checked
    property bool   child:                  false
    property bool   highlightSelected:      true         //是否要外围小圈
    property var    color:                  checked ? "green" : "orange" /*(child ? qgcPal.mapIndicatorChild : qgcPal.mapIndicator)*/   //此颜色为缩写字体背景色，聚焦为绿否则为橙色
    property real   anchorPointX:           _height / 2
    property real   anchorPointY:           _height / 2
    property bool   specifiesCoordinate:    true
    property bool   showSequenceNumbers:    true
    property real   _width:             1
    property real   _height:            1
    property real   _gimbalYawRadius:   10
    property real   _gimbalYawWidth:    _gimbalYawRadius * 2
    property real   _smallRadiusRaw:    15
    property real   _smallRadius:       _smallRadiusRaw + ((_smallRadiusRaw % 2 == 0) ? 1 : 0) // odd number for better centering
    property real   _normalRadiusRaw:   18
    property real   _normalRadius:      _normalRadiusRaw + ((_normalRadiusRaw % 2 == 0) ? 1 : 0)
    property real   _indicatorRadius:   small ? _smallRadius : _normalRadius
    property real   _labelMargin:       2
    property real   _labelRadius:       _indicatorRadius + _labelMargin
    property string _label:             label.length > 1 ? label : ""   //_label为在indicator旁的字，当长度大于1时为lable否则为空
    property string _index:             index
    property real lastX
    property real lastY

    function degreesToRadians(degrees) {
        return (Math.PI/180)*degrees
    }

    //聚焦时动态显示变化
    Behavior on _indicatorRadius { PropertyAnimation {} }

    Rectangle {
        id:                     labelControl
        anchors.leftMargin:     -((_labelMargin * 2) + indicator.width)
        anchors.rightMargin:    -(_labelMargin * 2)
        anchors.fill:           labelControlLabel
        color:                  "white"         //横向字体背景色
        opacity:                0.5
        radius:                 _labelRadius
        visible:                _label.length !== 0 && !small
    }

    Label {
        id:                     labelControlLabel
        anchors.topMargin:      -_labelMargin
        anchors.bottomMargin:   -_labelMargin
        anchors.leftMargin:     _labelMargin
        anchors.left:           indicator.right
        anchors.top:            indicator.top
        anchors.bottom:         indicator.bottom
        color:                  "black"          //全拼字体色
        text:                   _label
        verticalAlignment:      Text.AlignVCenter
        visible:                labelControl.visible
    }

    Rectangle {
        id:                             indicator
        anchors.horizontalCenter:       parent.left
        anchors.verticalCenter:         parent.top
        anchors.horizontalCenterOffset: anchorPointX
        anchors.verticalCenterOffset:   anchorPointY
        width:                          _indicatorRadius * 2
        height:                         width
        color:                          root.color     //颜色这里需要改一下，看聚焦与否
        radius:                         _indicatorRadius
        Rectangle{
            width: parent.width/4
            height: width
            color: parent.color
            radius: width/2
        }
        Rectangle{
            anchors.right: parent.right
            anchors.top: parent.top
            width: parent.width/4
            height: width
            color: parent.color
            radius: width/2
        }
        Rectangle{
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: parent.width/4
            height: width
            color: parent.color
            radius: width/2
        }
        Rectangle{
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: parent.width/4
            height: width
            color: parent.color
            radius: width/2
        }

        Label {
            anchors.fill:           parent
            horizontalAlignment:    Text.AlignHCenter
            verticalAlignment:      Text.AlignVCenter
            color:                  "white"          //中心缩写字颜色
            fontSizeMode:           Text.Fit
            text:                   index            //显示内容，任务点的标号
        }
    }

    // Extra circle to indicate selection
    Rectangle {
        width:          indicator.width * 2
        height:         width
        radius:         width * 0.5
        color:          Qt.rgba(0,0,0,0)
        border.color:   Qt.rgba(1,1,1,0.5)
        border.width:   1
        visible:        checked && highlightSelected
        anchors.centerIn: indicator
    }

    // The mouse click area is always the size of a normal indicator
//    Item {
//        id:                 mouseAreaFill
//        anchors.margins:    small ? -(_normalRadius - _smallRadius) : 0
//        anchors.fill:       indicator
//    }

    MouseArea {
        z:5
        anchors.fill:   indicator

        onClicked: {
            focus = true
            //checked = true
            parent.clicked(index)

            lastX = mouseX
            lastY = mouseY
        }

        onPositionChanged: {
            if (pressed&&checked) {
                //鼠标按住的前提下，坐标改变时，计算偏移量，应用到目标item的坐标上即可
                root.x += mouseX - lastX
                root.y += mouseY - lastY
                EquitmentControl.missionController.polygons.missiondrag(index,root.x,root.y)
                //console.log(root.x,root.y)
            }
        }
    }
}

