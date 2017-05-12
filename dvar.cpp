#include "stdafx.h"

Dvar::Dvar(dvar_s _dvar, QTreeWidget *_dvarTree) : dvar(_dvar)
{
	QString dvarSetting = QString("dvar_%1").arg(dvar.name);
	QSettings settings;

	QTreeWidgetItem* Item = new QTreeWidgetItem(_dvarTree, QStringList() << dvar.name);
	Item->setText(0, dvar.name);
	Item->setToolTip(0, dvar.description);

	QCheckBox* checkBox;
	QSpinBox* spinBox;
	QLineEdit* textBox;
	QComboBox* comboBox;

	switch(this->dvar.type)
	{
	case DVAR_VALUE_BOOL:
		checkBox = new QCheckBox();
		checkBox->setChecked(settings.value(dvarSetting, false).toBool());
		checkBox->setToolTip("Boolean value, check to enable or uncheck to disable.");
		_dvarTree->setItemWidget(Item, 1, checkBox);
		break;
	case DVAR_VALUE_INT:
		spinBox = new QSpinBox();
		spinBox->setValue(settings.value(dvarSetting, 0).toInt());
		spinBox->setToolTip("Integer value, min to max any number.");
		spinBox->setMaximum(dvar.maxValue);
		spinBox->setMinimum(dvar.minValue);
		_dvarTree->setItemWidget(Item, 1, spinBox);
		break;
	case DVAR_VALUE_STRING:
		textBox = new QLineEdit();
		textBox->setText(settings.value(dvarSetting, "").toString());
		textBox->setToolTip(QString("String value, leave this blank for it to not be used."));
		textBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
		_dvarTree->setItemWidget(Item, 1, textBox);
		break;
	case DVAR_VALUE_COMBO:
		comboBox = new QComboBox();
		QStringList mShippedMapList;
		mShippedMapList << "mp_aerospace" <<  "mp_apartments" << "mp_arena" << "mp_banzai" << "mp_biodome" << "mp_chinatown" << "mp_city" << "mp_conduit" << "mp_crucible" << "mp_cryogen" << "mp_ethiopia" << "mp_freerun_01" << "mp_freerun_02" << "mp_freerun_03" << "mp_freerun_04" << "mp_havoc" << "mp_infection" << "mp_kung_fu" << "mp_metro" << "mp_miniature" << "mp_nuketown_x" << "mp_redwood" << "mp_rise" << "mp_rome" << "mp_ruins" << "mp_sector" << "mp_shrine" << "mp_skyjacked" << "mp_spire" << "mp_stronghold" << "mp_veiled" << "mp_waterpark" << "mp_western" << "zm_castle" << "zm_factory" << "zm_genesis" << "zm_island" << "zm_levelcommon" << "zm_stalingrad" << "zm_zod";
		comboBox->addItems(mShippedMapList);
		comboBox->setEditable(true);
		_dvarTree->setItemWidget(Item,1,comboBox);
	}
}

Dvar::~Dvar()
{
}

dvar_s Dvar::findDvar(QString _dvarName, QTreeWidget* DvarTree, dvar_s* dvars, int DvarSize)
{
	dvar_s _dvar;
	for(int DvarIdx = 0; DvarIdx < DvarSize; DvarIdx++)
	{
		_dvar = Dvar(dvars[DvarIdx], DvarTree).dvar;
		if(_dvar.name == _dvarName)
			return _dvar;
	}
	return _dvar;
}

QString Dvar::setDvarSetting(dvar_s _dvar, QCheckBox* _checkBox)
{
	QSettings Settings;
	Settings.setValue(QString("dvar_%1").arg(_dvar.name), _checkBox->isChecked());

	return Settings.value(QString("dvar_%1").arg(_dvar.name)).toString() == "true" ? "1" : "0"; // another way to do this?
}

QString Dvar::setDvarSetting(dvar_s _dvar, QSpinBox* _spinBox)
{
	QSettings Settings;
	Settings.setValue(QString("dvar_%1").arg(_dvar.name), _spinBox->value());

	return Settings.value(QString("dvar_%1").arg(_dvar.name)).toString();
}

QString Dvar::setDvarSetting(dvar_s _dvar, QLineEdit* _lineEdit)
{
	QSettings Settings;
	Settings.setValue(QString("dvar_%1").arg(_dvar.name), _lineEdit->text());

	return Settings.value(QString("dvar_%1").arg(_dvar.name)).toString();
}

QString Dvar::setDvarSetting(dvar_s _dvar, QComboBox* _lineEdit)
{
	QSettings Settings;
	Settings.setValue(QString("dvar_%1").arg(_dvar.name), _lineEdit->currentText());
	return Settings.value(QString("dvar_%1").arg(_dvar.name)).toString();
	
}