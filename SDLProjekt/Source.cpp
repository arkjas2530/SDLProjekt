
#include "Menu.h"

using namespace std;



int main(int argc, char* args[])
{
	
	Menu menu;
	menu.firstLevel();



	/*outHeader a;
	
	ifstream file;
	file.open("out.asd", ios_base::binary);
	file.read(reinterpret_cast<char*>(&a),sizeof(a));
	file.seekg(22, ios_base::beg);
	cout << a.capacityForTab;

	vector<char> check;
	check.resize(a.capacityForTab);
	file.read(reinterpret_cast<char*>(&check[0]), a.capacityForTab);
	vector<int> check2;
	check2.resize(a.capacityForTab);
	/**/
	
	system("pause");
	return 0;
}