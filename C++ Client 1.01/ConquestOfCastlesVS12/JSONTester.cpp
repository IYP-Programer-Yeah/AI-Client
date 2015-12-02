#include <iostream>
#include <string>

#include "easylogging++.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

#include "Commands.h"

using namespace std;
using namespace ConquestOfCastles;
using namespace rapidjson;

INITIALIZE_EASYLOGGINGPP

int main() {
	StringBuffer sb;
	Writer<StringBuffer> writer(sb);
	
	AttackCommand attack(0,Vector2D(1,2));
	attack.Serialize(writer);

	LOG(DEBUG) << sb.GetString();
	system("pause");
	return 0;
}