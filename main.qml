import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Connections {
        target: SerialCommInstance
        onGetSerialData:
        {
            mTextArea.append(data)
        }
    }

    Column{
        spacing: 10
        TextArea{
            id: mTextArea
            width: 400
            height: 300
        }
        Row {
            spacing: 10
            Button {
                id: connectBtn
                text: qsTr("Connect")
                checked: false
                onClicked: {
                    SerialCommInstance.openSerialPortSlot(comboBoxNames.currentText, comboBoxBauds.currentIndex)
                    checked = true
                    disconnectBtn.checked = false
                }
            }
            Button {
                id: disconnectBtn
                text: qsTr("Disconnect")
                checked: true
                onClicked: {
                    SerialCommInstance.closeSerialPortSlot()
                    checked = true
                    connectBtn.checked = false
                }
            }
        }

        Row {
            spacing: 50
            ComboBox {
                id: comboBoxBauds
                model: portsName
            }

            ComboBox {
                id: comboBoxNames
                model: baudRates
            }
        }
    }
}
