#include <iostream>
#include "StatickaLL.h"

int main(void)
{
	StatickaLL<10> listica;

	listica.add_to_head(1);
	listica.add_to_head(2);
	listica.add_to_head(7);
	listica.add_to_head(5);
	listica.add_to_head(0);
	listica.add_to_head(3);

	listica.print();

	listica.sort_bubble();
	
	listica.print();

	listica.move_part_to_end(1, 1);

	listica.print();

	listica.sort_bubble();

	listica.print();

	listica.move_part_to_end(1, 1);

	listica.print();

	listica.sort_bubble();

	listica.print();

	listica.update_at(0, 10);

	listica.add_to_head(12);
	listica.add_to_head(13);
	listica.add_to_head(14);
	listica.add_to_head(15);

	listica.print();


	StatickaLL<20> l2;

	l2.add_to_head(1);
	l2.add_to_head(3);
	l2.add_to_head(6);
	l2.add_to_head(7);
	l2.add_to_head(7);

	l2.sort_bubble();

	l2.print();

	l2.fill_in_the_blanks();

	l2.print();

	l2.add_to_head(10);
	l2.add_to_head(11);
	l2.add_to_head(12);
	l2.add_to_head(13);

	l2.print();

	return 0;
}