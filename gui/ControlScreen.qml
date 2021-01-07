import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import "control"

ColumnLayout {
	Label {
		text: qsTr("Control screen")
		font.pixelSize: Qt.application.font.pixelSize * 2
		padding: 10
	}

	TabBar {
		id: tabBar
		Layout.fillWidth: true
		TabButton {
			text: qsTr("Nodes")
		}
		TabButton {
			text: qsTr("Logic")
		}
	}

	StackLayout {
		currentIndex: tabBar.currentIndex
		Layout.fillWidth: true

		NodeControl {
			id: nodeControl
		}
		LogicControl {
			id: logicControl
		}
	}
}
