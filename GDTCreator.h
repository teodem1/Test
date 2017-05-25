#pragma once
#include "mlMainWindow.h" //Hmmm, I Don't Know Why I Need To Force That Here...

class GDTCreator : public QGroupBox
{
private:
	mlMainWindow* parentWindow;

	QDir* source_data_folder;
	QDir* model_export_folder;


protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragLeaveEvent(QDragLeaveEvent* event);
	void dropEvent(QDropEvent *event);
	void MakeGDT(QString, QString, QString, QString); //Type, Extension, Name, Path


public:
	GDTCreator(QWidget *parent, mlMainWindow* parent_window);
};
