#pragma once
#define TextOK 0
#define TextError -1
#define TextNoPrev -2
class TDataCom
{
protected:
	int RetCode;
	int SetRetCode(int ret)
	{
		return RetCode = ret;
	}
public:
	TDataCom() :RetCode(TextOK) {}
	virtual ~TDataCom() {};
	int GetRetCode()
	{
		int temp = RetCode;
		RetCode = TextOK;
		return temp;
	}
};
//#ifndef __DATVALUE_H
//#define __DATVALUE_H
//#include <iostream>
//class TDatValue
//{
//public:
//	virtual TDatValue* GetCopy() = 0;
//	~TDatValue() {}
//};
//typedef TDatValue* PTDatValue;
//#endif