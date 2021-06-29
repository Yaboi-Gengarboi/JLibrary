// JLibraryIdeaTest
// main.cpp
// Created on 2021-06-11 by Justyn Durnford
// Last modified on 2021-06-20 by Justyn Durnford

import Point2;
import Vector2;

#include "Arithmetic.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	jlib::Point2<int> P(3, 5);
	jlib::Point2<int> Q(4, 2);
	
	if (P != Q)
		cout << P.toString();

	return 0;
}