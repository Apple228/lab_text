#ifndef __DATACOM_H__
#define __DATACOM_H__
#define DataOK   0
#define DataErr -1
// TDataCom €вл€етс€ общим базовым классом
class TDataCom
{
protected:
    int RetCode; //  од завершени€
    int SetRetCode(int ret) { return RetCode = ret; }
public:
    TDataCom() : RetCode(DataOK) {}
    virtual ~TDataCom() {}
    int GetRetCode()
    {
        int temp = RetCode;
        RetCode = DataOK;
        return temp;
    }
};
#endif