#include "stdafx.h"

GDTCreatorGroupBox::GDTCreatorGroupBox(QWidget* parent, mlMainWindow* parent_window) : QGroupBox(parent), parentWindow(parent_window)
{
	this->setAcceptDrops(true);
}

void GDTCreatorGroupBox::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void GDTCreatorGroupBox::dropEvent(QDropEvent* event)
{
	const QMimeData* mimeData = event->mimeData();

	if (parentWindow == NULL)
	{
		return;
	}

	if (mimeData->hasUrls())
	{
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();

		QDir working_dir(parentWindow->mToolsPath);
		for (int i = 0; i < urlList.size(); i++)
		{
			pathList.append(urlList.at(i).toLocalFile());
		}

		QProcess* Process = new QProcess();
		connect(Process, SIGNAL(finished(int)), Process, SLOT(deleteLater()));

		bool allowOverwrite = this->parentWindow->mGDTCreateOverwriteWidget->isChecked();

		QString outputDir = parentWindow->mGDTCreateTargetDir->text();
		parentWindow->StartConvertThread(pathList, outputDir, allowOverwrite);

		event->acceptProposedAction();
	}
}

void GDTCreatorGroupBox::dragLeaveEvent(QDragLeaveEvent* event)
{
	event->accept();
}