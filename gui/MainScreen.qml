import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Window {
	visible: true
	width: 640
	height: 640
	title: qsTr("Helloapp")

	GridLayout {
		id: headerLayout
		columns: 3
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top

		Text {
			text: "Socket ID:"
		}
		Text {
			text:  "MAC-address:"
		}
		Text {
			text:  "Ready for use:"
		}
	}

	ListView {
		id: nodeList
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: headerLayout.bottom
		anchors.bottom: parent.bottom

		clip: true
		flickableDirection: Flickable.AutoFlickIfNeeded
		model: qController.qConnectionList

		delegate: GridLayout {
			columns: 3
			anchors.left: parent.left
			anchors.right: parent.right

			Text {
				text: modelData.qSocketDescriptor
				elide: Text.ElideRight
			}

			Text {
				text: modelData.qNodeInfoData.qMacAddress
				elide: Text.ElideRight
			}

			CheckBox {
				checked: modelData.qNodeInfoData.qReadyForUse
				enabled: false
			}
		}
	}
}
