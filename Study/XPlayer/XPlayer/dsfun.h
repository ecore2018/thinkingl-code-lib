#pragma once

/**
*	��һЩDirectShow���ܵĺ�����װ.
*	+by lizhixing@2015-06-07
*/

#include <dshow.h>

// ֧��GraphEdit���Գ���.
HRESULT AddToRot( IUnknown * pUnknownGraph, DWORD* pdwRegister );

void RemoveFromRot( DWORD pdwRegister);