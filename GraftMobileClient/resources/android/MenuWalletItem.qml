import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import com.graft.design 1.0

MenuItem {
    property alias balanceInGraft: graftMoney.text
    property alias menuIcon: menuLabel.labelIcon
    property alias menuName: menuLabel.labelName

    padding: 0
    topPadding: 0
    bottomPadding: 0
    contentItem: Item {

        RowLayout {
            anchors {
                fill: parent
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            MenuLabel {
                id: menuLabel
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
                labelName: qsTr("Wallet")
                labelIcon: "qrc:/imgs/waller.png"
            }

            Label {
                id: graftMoney
                Layout.alignment: Qt.AlignRight
                color: ColorFactory.color(DesignFactory.MainText)
                font {
                    bold: true
                    family: "Liberation Sans"
                    pixelSize: 15
                }
            }

            Image {
                Layout.preferredHeight: 23
                Layout.preferredWidth: 23
                Layout.alignment: Qt.AlignRight
                source: "qrc:/imgs/g-min.png"
            }
        }
    }
}
