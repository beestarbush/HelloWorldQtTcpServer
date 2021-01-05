import QtQuick 2.0
import QtQuick.Window 2.10
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Page {
	Image {
		id: image
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.top: parent.top
		anchors.bottom: parent.bottom
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
		text: "File not found!"
		visible: true
		anchors.centerIn: parent
	}
}

