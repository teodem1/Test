#pragma once

class GDTCreatorGroupBox : public QGroupBox
{
private:
	mlMainWindow* parentWindow;

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragLeaveEvent(QDragLeaveEvent* event);
	void dropEvent(QDropEvent *event);

public:
	GDTCreatorGroupBox(QWidget *parent, mlMainWindow* parent_window);
};