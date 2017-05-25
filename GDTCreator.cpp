#include "stdafx.h"
#include "mlMainWindow.h"

void GDTCreator::dropEvent(QDropEvent* event)
{
	if (parentWindow == NULL)
		return;

	source_data_folder = new QDir(QString("%1/source_data").arg(parentWindow->mToolsPath));
	model_export_folder = new QDir(QString("%1/model_export").arg(parentWindow->mToolsPath));
	QStringList AllowedFileTypes = (QStringList() << "tiff" << "tif" << "xmodel_bin");


	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> FileList = event->mimeData()->urls();
		QString GDTType, FileName, Path;
		for (int i = 0; i < FileList.size(); i++)
		{	
			QFileInfo CurrentFile = FileList.at(i).toLocalFile();

			if(!AllowedFileTypes.contains(CurrentFile.suffix()))
			{
				QMessageBox::information(this,"Hold Up!",QString("Sorry, I Don't Support The File Type: %1").arg(CurrentFile.suffix()),QMessageBox::Ok);
				return;
			}			

			if(CurrentFile.isDir())
			{
				QMessageBox::information(this,"Hold Up!","Sorry, I Don't Support Folders! Please Drag The Files Onto Me.",QMessageBox::Ok);
				/*QDirIterator Iterator(CurrentFile.absolutePath(), QStringList() << "*.tif" << "*.tiff" << "*.xmodel_bin");
				while(Iterator.hasNext())
				{
					GDTType = GetGDTType(Iterator.next());
					FileName = GetGDTFileName(Iterator.next().split(".",QString::SkipEmptyParts).at(0));

					MakeGDT(GDTType,FileName,QFileInfo(Iterator.next()).suffix(),
				}*/
				return;
			}

			QString WorkingDir = QFileInfo(CurrentFile).fileName().split(".",QString::SkipEmptyParts).at(0);
			QString SavePath = QString("%1/%2").arg(model_export_folder->absolutePath(),WorkingDir);

			if(parentWindow->mAutoCopyAssetsAfterGDTCreation->isChecked())
			{
				if(!QDir().exists(SavePath))
					QDir().mkpath(SavePath);

				QFile().copy(FileList.at(i).toLocalFile(),QString("%1/%2/%3").arg(model_export_folder->absolutePath(),WorkingDir,CurrentFile.fileName()));
				Path = QString("%1/%2/%3").arg("model_export",WorkingDir,CurrentFile.fileName());
			}
			else
			{
				Path = FileList.at(i).toLocalFile();
			}
	
			GDTType = GetGDTType(CurrentFile);

			if(!GDTType.isEmpty())
			{
				FileName = GetGDTFileName(WorkingDir);
				MakeGDT(GDTType, FileName, CurrentFile.suffix(),Path);
			}
		}
	}

	if(parentWindow->mOpenAPEAfterCreation->isChecked())
		parentWindow->mActionFileAssetEditor->trigger();

	event->acceptProposedAction();
}

GDTCreator::GDTCreator(QWidget* parent, mlMainWindow* parent_window) : QGroupBox(parent), parentWindow(parent_window)
{
	this->setAcceptDrops(true);
}

void GDTCreator::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void GDTCreator::dragLeaveEvent(QDragLeaveEvent* event)
{
	event->accept();
}

void GDTCreator::MakeGDT(QString Type, QString Name, QString Extension, QString Path)
{
	QString Template;
	QFile* GDTFile;

	if(Type == "xmodel" && Extension == "xmodel_bin")
	{
		Template = 
			"{\n" +
			QString("\t\"%1\" ( \"xmodel.gdf\" )\n").arg(Name) +
			"\t{\n" +
			"\t\t\"filename\" \"" + Path + "\"\n" +
			"\t\t\"highLodDist\" \"751\"\n" + 
			"\t\t\"type\" \"rigid\"\n" +
			"\t}\n" +
			"}\n";

		GDTFile = new QFile(QString("%1/%2.%3").arg(source_data_folder->absolutePath(),Name,"gdt"));
		if(GDTFile->open(QFile::ReadWrite))
		{
			QTextStream FileWriter(GDTFile);
			FileWriter << Template;
			FileWriter.flush();
			GDTFile->close();
		}
		else
		{
			QMessageBox::critical(this,"Uh-Oh!","I Couldn't Open The File For Saving",QMessageBox::Ok);
			return;
		}
	}
	else if(Type == "image" && Extension == "tiff" || Extension == "tif")
	{
		Template = 
			"{\n" + 
			QString("\t\"%1\" ( \"image.gdf\" )\n").arg(Name) +
			"\t{\n" +
			"\t\t\"baseImage\" \"" + Path +"\"\n" +
			"\t\t\"semantic\" \"diffuseMap\"\n" +
			"\t\t\"imageType\" \"Texture\"\n" +
			"\t\t\"type\" \"image\"\n" +
			"\t\t\"compressionMethod\" \"uncompressed\"\n" +
			"\t}\n" +
			"}\n";

		GDTFile = new QFile(QString("%1/%2.%3").arg(source_data_folder->absolutePath(),Name,"gdt"));
		if(GDTFile->open(QFile::ReadWrite))
		{
			QTextStream FileWriter(GDTFile);
			FileWriter << Template;
			FileWriter.flush();
			GDTFile->close();
		}
		else
		{
			QMessageBox::critical(this,"Uh-Oh!","I Couldn't Open The File For Saving",QMessageBox::Ok);
			return;
		}
	}
}

QString GDTCreator::GetGDTType(QFileInfo CurrentFile)
{
	QInputDialog GDTType;
	QString GDTTemplate;
	int Ret;

	GDTType.setOption(QInputDialog::UseListViewForComboBoxItems);
	GDTType.setWindowTitle("GDT Creation Type");
	GDTType.setLabelText(QString("What Type Of GDT Should I Create?\nAsset: %1").arg(CurrentFile.fileName()));
	GDTType.setComboBoxItems(QStringList() << "xmodel" << "image");

	do
	{
		Ret = GDTType.exec();
	}while(Ret != QDialog::Accepted);

	if(!GDTType.textValue().isEmpty())
		return GDTType.textValue();
}

QString GDTCreator::GetGDTFileName(QString WorkingDir)
{
	QString FileName = WorkingDir.left(WorkingDir.lastIndexOf('_'));
	QInputDialog FileNameInput;
	FileNameInput.setInputMode(QInputDialog::TextInput);
	FileNameInput.setWindowTitle("File Name");
	FileNameInput.setLabelText("What Should I Call The GDT?");
	bool Res;

	do
	{
		FileName = FileNameInput.getText(this,"File Name","What Should I Call The GDT?",QLineEdit::Normal,FileName, &Res);
	}while(Res != true);

	parentWindow->mOutputWidget->appendPlainText(FileName);
	return FileName;
}