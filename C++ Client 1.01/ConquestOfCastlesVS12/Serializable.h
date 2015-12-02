#pragma once
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "rapidjson\writer.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;
using namespace rapidjson;

namespace ConquestOfCastles {
	class Serializable {
	public:
		virtual void Serialize(Writer<StringBuffer>& writer) = 0;
	};
}

#endif