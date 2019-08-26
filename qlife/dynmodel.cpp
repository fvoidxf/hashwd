/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#include <stdexcept>
#include "dynmodel.h"

//-------------------------------------------------------------------------------------------------
DynModel::DynModel(int N, int M)
    :n(N)
    ,m(M)
{

}

//-------------------------------------------------------------------------------------------------
DynModel::~DynModel()
{
    free();
}

//-------------------------------------------------------------------------------------------------
bool DynModel::allocate()
{
    data = (unsigned char **)(new unsigned char*[n]);
    for(auto i = 0; i < n; i++)
    {
        data[i] = new unsigned char[m];
    }
    return true;
}

//-------------------------------------------------------------------------------------------------
unsigned char& DynModel::item(int i, int j)
{
    if( (i < 0) || (i >= n) )
        throw std::range_error("invalid i index");
    if( (j < 0) || (j >= m) )
        throw std::range_error("invalid j index");
    return data[i][j];
}

//-------------------------------------------------------------------------------------------------
unsigned char& DynModel::operator()(int i, int j)
{
    return item(i,j);
}

//-------------------------------------------------------------------------------------------------
void DynModel::free()
{
    for(auto i = 0; i < n; i++)
        delete[] data[i];
    delete data;
}

//-------------------------------------------------------------------------------------------------
void DynModel::clear()
{
    for(auto i = 0; i < n; i++)
        for(auto j = 0; j < m; j++)
            data[i][j] = 0;
}

//-------------------------------------------------------------------------------------------------
