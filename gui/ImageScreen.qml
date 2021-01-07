import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

ColumnLayout {
	Layout.fillWidth: true
	Layout.fillHeight: true

	Image {
		id: image
		Layout.fillWidth: true
		Layout.fillHeight: true
		source: "file:files/" + qApplicationData.qActiveFilename
		fillMode: Image.PreserveAspectCrop
		clip: true

		onStatusChanged: {
			if (image.status === Image.Error)
			{
				image.visible = false
				errorText.visible = true
			}
			else
			{
				image.visible = true
				errorText.visible = false
			}
		}
	}
	Text {
		id: errorText
		text: qsTr("File not found!")
		visible: true
	}
}
