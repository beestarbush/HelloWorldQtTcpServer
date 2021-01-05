import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item {
	GridLayout {
		id: headerLayout
		columns: 3
		anchors.top: parent.top
		anchors.topMargin: 50
		anchors.left: parent.left
		anchors.right: parent.right

		Text {
			text: "Socket ID:"
			font.bold: true
		}
		Text {
			text:  "MAC-address:"
			font.bold: true
		}
		Text {
			text:  "Ready for use:"
			font.bold: true
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

