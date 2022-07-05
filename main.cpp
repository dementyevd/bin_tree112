#include "tree112.h"

void main() {
	bin_tree<char, char> tree1;
	tree1.insert('a', 'A');
	tree1.insert('c', 'C');
	tree1.insert('v', 'V');
	tree1.insert('b', 'B');
	tree1.insert('f', 'F');
	tree1.insert('c', 'C');
	tree1.insert('c', 'C');
	tree1.insert('c', 'C');
	tree1.insert('h', 'H');
	tree1.print();
	tree1.find('h')->val = 'w';
	cout << endl << endl;
	tree1.remove('c');
	tree1.print();

}