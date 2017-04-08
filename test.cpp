#include"GraphList.h"
#include<iostream>
using std::cout;

int main() {
	GraphList gl(5);
	for (size_t i = 1; i < 5; ++i)
		gl.setEdge(0, i, 2);

	gl.delEdge(0, 3);

	cout << gl.e() << '\n';
	gl.setEdge(3, 0);
	cout << gl.e() << '\n';
	cout << gl.hasEdge(0, 3) << ' '
		<< gl.hasEdge(3, 0) << '\n';

	cout << gl.weight(0, 3) << ' '
		<< gl.weight(3, 0) << '\n';
}