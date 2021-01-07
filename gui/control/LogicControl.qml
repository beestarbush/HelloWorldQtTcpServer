import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

ColumnLayout {
	Layout.fillWidth: true

	GridLayout {
		id: infoLayout
		columns: 2
		Layout.fillWidth: true

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

	GridLayout {
		Layout.topMargin: 20
		Layout.fillWidth: true
		Layout.fillHeight: true
		columns: 1

		Text {
			text: qsTr("Unknown IDs")
			font.bold: true
			Layout.fillWidth: true
		}

		Button {
			text: qsTr("Clear");
			onClicked: qApplicationData.qUnknownIds = "";
			Layout.fillWidth: true
		}

		TextArea {
			Layout.fillHeight: true
			text: qApplicationData.qUnknownIds
		}
	}
}
