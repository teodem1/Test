#pragma once

enum COD2MAPArgType
{
	ARG_VALUE_SET, // Just Needs To Be Set.
	ARG_VALUE_NEEDS_INT, //Needs User INT Input.
	ARG_VALUE_NEEDS_COMBO, //Needs User To Choose Strig From List.
	ARG_VALUE_NEEDS_STRING //Needs String
};

struct COD2MAPArg_s
{
	const char* name;
	const char* description;
	COD2MAPArgType type;
	int minValue;
	int maxValue;
	bool isSettable;//Is Settable, Needs No Value. E.G. -
	QStringList DataCollection; //Over Kill? Probably. Bad Practice? Most Defiantly. Do I Care? You bet not.
};

class COD2MAP
{
private:
	COD2MAPArg_s CurrentArg;


public:
	COD2MAP();
	COD2MAP(COD2MAPArg_s, QTreeWidget*);
	~COD2MAP();

	static QString setCOD2MAPSetting(COD2MAPArg_s, QCheckBox*);
	static QString setCOD2MAPSetting(COD2MAPArg_s, QLineEdit*);

	static COD2MAPArg_s findSetting(QString, QTreeWidget*, COD2MAPArg_s*, int);
};