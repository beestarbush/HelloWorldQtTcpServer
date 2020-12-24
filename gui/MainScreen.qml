import QtQuick 2.10
import QtQuick.Window 2.10

Window {
    visible: true
    width: 640
    height: 640
    title: qsTr("Hello World")

    Text {
        id: firstText
        text: "Hello World!"
    }
}
