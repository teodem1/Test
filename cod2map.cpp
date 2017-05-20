#include "stdafx.h"

COD2MAP::COD2MAP(COD2MAPArg_s Argument, QTreeWidget* ArgumentTree)
{
	QString Setting = QString("Setting_%1").arg(Argument.name);
	QSettings settings;

	QTreeWidgetItem* Item = new QTreeWidgetItem(ArgumentTree, QStringList() << Argument.name);
	Item->setText(0, Argument.name);
	Item->setToolTip(0, Argument.description);

	QCheckBox* checkBox;
	QSpinBox* spinBox;
	QComboBox* comboBox;

	switch(Argument.type)
	{
	case ARG_VALUE_SET:
		checkBox = new QCheckBox();
		checkBox->setChecked(settings.value(Setting, false).toBool());
		checkBox->setToolTip("Boolean value, check to enable or uncheck to disable.");
		ArgumentTree->setItemWidget(Item, 1, checkBox);
		break;
	case ARG_VALUE_NEEDS_COMBO_TEXT:
		comboBox = new QComboBox();
		comboBox->setToolTip(QString("String value, leave this blank for it to not be used."));
		comboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		ArgumentTree->setItemWidget(Item, 1, comboBox);
		break;
	}
}

COD2MAPArg_s COD2MAP::findSetting(QString _SettingName, QTreeWidget* SettingTree, COD2MAPArg_s* Settings, int SettingsSize)
{
	COD2MAPArg_s Setting;
	for(int SettingIdx = 0; SettingIdx < SettingsSize; SettingIdx++)
	{
		Setting = COD2MAP(Settings[SettingIdx], SettingTree).CurrentArg;
		if(Setting.name == _SettingName)
			return Setting;
	}
	return Setting;
}

QString COD2MAP::setCOD2MAPSetting(COD2MAPArg_s Setting, QCheckBox* _checkBox)
{
	QSettings Settings;
	Settings.setValue(QString("Setting_%1").arg(Setting.name), _checkBox->isChecked());

	return Settings.value(QString("Setting_%1").arg(Setting.name)).toString() == "true" ? "1" : "0"; // another way to do this?
}

QString COD2MAP::setCOD2MAPSetting(COD2MAPArg_s Setting, QLineEdit* _textBox)
{
	QSettings Settings;
	Settings.setValue(QString("Setting_%1").arg(Setting.name), _textBox->text());

	return Settings.value(QString("Setting_%1").arg(Setting.name)).toString();
}

COD2MAP::~COD2MAP()
{
}