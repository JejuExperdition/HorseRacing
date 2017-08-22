#include "Error.h"
#include <stdlib.h>
#include <Windows.h>

void error(const char *str)
{
	OutputDebugStringA(str);
	exit(1);
}

void errorByHresult(HRESULT hr, const char* str)
{
	if (FAILED(hr)) error(str);
}