#pragma once
#include "Location.h"
#include "MyException.h"
#include <functional>
#include "utilties.h"

using FunctionPtr = std::function<double(const Location&, const Location&)>;
using FunMap = std::map<int, FunctionPtr>;


FunctionPtr getFunction(const char& c);


FunctionPtr getDistFunction();