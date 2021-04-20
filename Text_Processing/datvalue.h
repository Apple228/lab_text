//#pragma once
//#ifndef __DATTYPE_H__
//#define __DATTYPE_H__
//
//// Id for DatValue
//enum DatValueType
//{
//	NONE = -1, INT_VALUE, DOUBLE_VALUE, MONOM, REC_ROOT, TAB_RECORD, TREE_NODE
//};
//
//#endif
#ifndef __DATVALUE_H
#define __DATVALUE_H
#include <iostream>
class TDatValue
{
public:
	virtual TDatValue* GetCopy() = 0;
	~TDatValue() {}
};
typedef TDatValue* PTDatValue;
#endif