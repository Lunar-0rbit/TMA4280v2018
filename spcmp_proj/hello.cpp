#include <iostream>
#include "topologymesh.h"
#include "topomesh1d.h"
using namespace std;

int main()
{
	Topology tp1(4,3,20);
	tp1.retrieve_coordinates(81);
	cout << "\n" << tp1.coordinates[0] << "\n";
	cout << "\n" << tp1.coordinates[1] << "\n";
	
	Topology1s tp1d(4,3,10);
	tp1d.retrieve_coordinates(2);
	cout << 7/3 << "\n";
	
return 0;

}