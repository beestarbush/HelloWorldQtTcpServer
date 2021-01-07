import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

ColumnLayout {
	Layout.fillWidth: true

	GridLayout {
		id: headerLayout
		columns: 3
		Layout.fillWidth: true

		Text {
			text: "Socket ID:"
			font.bold: true
			Layout.fillWidth: true
		}
		Text {
			text:  "MAC-address:"
			font.bold: true
			Layout.fillWidth: true
		}
		Text {
			text:  "Ready for use:"
			font.bold: true
			Layout.fillWidth: true
		}
	}

	ListView {
		id: nodeList
		Layout.fillWidth: true
		Layout.fillHeight: true

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
				Layout.fillWidth: true
			}

			Text {
				text: modelData.qNodeInfoData.qMacAddress
				elide: Text.ElideRight
				Layout.fillWidth: true
			}

			CheckBox {
				checked: modelData.qNodeInfoData.qReadyForUse
				enabled: false
				Layout.fillWidth: true
			}
		}
	}
}
