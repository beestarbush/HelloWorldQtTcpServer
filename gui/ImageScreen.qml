import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Page {
	header: Label {
		text: qsTr("Image")
		font.pixelSize: Qt.application.font.pixelSize * 2
		padding: 10
	}

	GridLayout {
		id: headerLayout
		columns: 2
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top

		Text {
			text: qsTr("Active combination:")
		}
		Text {
			text: qApplicationData.qActiveCombinationId
		}
		Text {
			text: qsTr("Active filename:")
		}
		Text {
			text: qApplicationData.qActiveFilename
		}
	}
}
