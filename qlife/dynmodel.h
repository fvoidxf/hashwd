/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
*/

#ifndef __DYNMODEL_H__
#define __DYNMODEL_H__

//=================================================================================================
class DynModel
{
protected:
    unsigned char **data;
    const int n;
    const int m;

public:
    DynModel(int N, int M);
    virtual ~DynModel();

    bool allocate();
    unsigned char& item(int i, int j);
    void free();
    void clear();
    unsigned char& operator()(int i, int j);
};

//=================================================================================================

#endif // __DYNMODEL_H__
