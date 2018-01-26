import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.2
import "../"

ColumnLayout {
    id: linearEditItem
    property alias title: titleItem.text
    property alias text: editItem.text
    property alias wrapMode: editItem.wrapMode
    property alias inputMethodHints: editItem.inputMethodHints
    property alias validator: editItem.validator
    property alias showLengthIndicator: textCount.visible
    property alias inputMask: editItem.inputMask
    property alias echoMode: editItem.echoMode
    property bool letterCountingMode: true
    property int maximumLength: 32767
    property alias passwordCharacter: editItem.passwordCharacter
    property bool passwordMode: false
    property bool wrongFieldColor: false
    property bool visibilityIcon: false
    property alias attentionText: attentionText
    property bool inlineTitle: false

    spacing: 0
    onPasswordModeChanged: {
        visibilityIcon = true
        if (passwordMode) {
            passwordCharacter = '•'
            editItem.echoMode = TextInput.Password
        } else {
            editItem.echoMode = TextInput.Normal
        }
    }

    TextField {
        id: editItem
        Layout.fillWidth: true
        Layout.bottomMargin: -12
        rightPadding: visibilityIcon ? 42 : 0
        verticalAlignment: Qt.AlignTop
        color: "#404040"
        leftPadding: titleItem.width
        bottomPadding: 30
        maximumLength: letterCountingMode ? linearEditItem.maximumLength : 32767
        Material.accent: wrongFieldColor ? "#F33939" : "#9E9E9E"

        onWrapModeChanged: {
            if (wrapMode === TextField.NoWrap) {
                Layout.fillHeight = false
                leftPadding = titleItem.width
                topPadding = 0
            } else {
                Layout.fillHeight = true
                if (!inlineTitle) {
                    leftPadding = 0
                    topPadding = 30
                    Layout.maximumHeight = 200
                }
            }
        }

        Text {
            id: titleItem
            anchors {
                top: parent.top
                left: parent.left
                bottom: parent.bottom
                topMargin: 8
            }
            font.pointSize: parent.font.pointSize
            rightPadding: 5
            color: "#8E8E93"
        }

        VisibilityIcon {
            z: 1
            visible: visibilityIcon
            anchors {
                right: parent.right
                bottom: parent.bottom
                rightMargin: 6
                bottomMargin: 12
            }
            Material.accent: "#9E9E9E"
            onClicked: passwordMode =! passwordMode
        }

        Item {
            height: 20
            width: height * 2
            anchors {
                right: parent.right
                bottom: parent.bottom
            }

            MouseArea {
                anchors.fill: parent
            }
        }
    }

    RowLayout {
        spacing: 0

        Text {
            id: attentionText
            font.pointSize: 12
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft
        }

        Text {
            id: textCount
            text: qsTr("%1/%2").arg(letterCountingMode ? editItem.length :
                                                         wordCounting()).arg(maximumLength)
            color: "#8E8E93"
            font.pointSize: 12
            Layout.topMargin: 0
            Layout.alignment: Qt.AlignRight
        }
    }

    function wordCounting() {
        if (editItem.displayText.length !== 0) {
            var wordList = GraftClient.wideSpacingSimplify(editItem.displayText).split(' ')
            return wordList.length
        } else {
            return 0
        }
    }
}
