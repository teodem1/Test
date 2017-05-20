#pragma once

enum COD2MAPArgType
{
	ARG_VALUE_SET, // Just Needs To Be Set.
	ARG_VALUE_NEEDS_INT_TEXT, //Needs User INT Input.
	ARG_VALUE_NEEDS_COMBO_TEXT //Needs User To Choose Strig From List.
};

struct COD2MAPArg_s
{
	const char* name;
	const char* description;
	COD2MAPArgType type;
	int minValue;
	int maxValue;
	bool isSettable;//Is Settable, Needs No Value. E.G. -
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