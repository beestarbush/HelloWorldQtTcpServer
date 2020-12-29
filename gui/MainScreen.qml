import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Window {
	visible: true
	width: 640
	height: 640
	title: qsTr("Helloapp")

	SwipeView {
		id: swipeView
		anchors.fill: parent
		currentIndex: 0

		ControlScreen {
			width: 600
			height: 400
		}

		ImageScreen {
			width: 600
			height: 400
		}
	}
}
