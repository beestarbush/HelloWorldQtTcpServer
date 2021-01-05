import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item {
	GridLayout {
		id: infoLayout
		columns: 2
		anchors.top: parent.top
		anchors.topMargin: 50
		anchors.left: parent.left
		anchors.right: parent.right

		Text {
			text: qsTr("Active combination:")
			font.bold: true
		}
		Text {
			text: qApplicationData.qActiveCombinationId
		}
		Text {
			text: qsTr("Active filename:")
			font.bold: true
		}
		Text {
			text: qApplicationData.qActiveFilename
		}
	}
}
