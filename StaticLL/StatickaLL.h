#pragma once

#include "Node.h"
#include <iostream>

template <int N>
class StatickaLL
{
private:
	Node m_data[N];
	int m_lrmp;
	int m_head;
	int m_size = N;

public:
	StatickaLL() : m_lrmp(0), m_head(-1)
	{
		for (int i = 0; i < m_size - 1; i++)
		{
			m_data[i].next = i + 1;
		}
		m_data[m_size - 1].next = -1;
	}
	~StatickaLL() {}

	bool is_empty() const
	{
		return m_head == -1;
	}

	bool is_full() const
	{
		return m_lrmp == -1;
	}

	bool add_to_head(int info)
	{
		if (is_full())
			return false;


		if (is_empty())
		{
			int tmp = m_lrmp;
			m_lrmp = m_data[m_lrmp].next;
			m_data[tmp].info = info;
			m_data[tmp].next = -1;
			m_head = tmp;

			return true;
		}

		int tmp = m_lrmp;
		m_lrmp = m_data[m_lrmp].next;

		m_data[tmp].info = info;
		m_data[tmp].next = m_head;
		m_head = tmp;

		return true;
	}

	bool remove_at(int info)
	{
		if (is_empty())
			return false;

		int prev = -1;
		int iter = m_head;

		while (iter != -1)
		{
			if (m_data[iter].info == info)
			{
				if (prev == -1)
				{
					int tmp = m_head;
					m_head = m_data[m_head].next;
					m_data[tmp].next = m_lrmp;
					m_lrmp = tmp;

					return true;
				}


				m_data[prev].next = m_data[iter].next;
				m_data[iter].next = m_lrmp;
				m_lrmp = iter;

				return true;

			}

			prev = iter;
			iter = m_data[iter].next;
		}

		return false;
	}

	bool swap_neighbour(int prev)
	{
		int swapable;
		if (prev != -1)
			swapable = m_data[prev].next;
		else
			swapable = m_head;

		if (m_data[swapable].next == -1)
			return false;

		int next_next = m_data[swapable].next;

		int tmp = m_data[next_next].next;
		m_data[next_next].next = swapable;
		m_data[swapable].next = tmp;
		if (prev != -1)
			m_data[prev].next = next_next;
		else
			m_head = next_next;

		return true;
	}

	bool swap(int prev1, int prev2)
	{
		if (prev1 == -1)
		{
			if (prev2 == m_head)
			{
				swap_neighbour(m_head);
				return true;
			}
		}

		if (m_data[prev1].next == prev2)
		{
			swap_neighbour(prev1);
			return true;
		}

		if (m_data[prev2].next == prev1)
		{
			swap_neighbour(prev2);
			return true;
		}


		int ptr1;
		if (prev1 != -1)
			ptr1 = m_data[prev1].next;
		else
			ptr1 = m_data[m_head].next;

		int ptr2 = m_data[prev2].next;

		if (ptr2 == -1)
			return false;

		int tmp = m_data[ptr2].next;
		m_data[ptr2].next = m_data[ptr1].next;
		m_data[ptr1].next = tmp;

		if (prev1 != -1)
			m_data[prev1].next = ptr2;
		else
			m_data[m_head] = ptr2;

		m_data[prev2].next = ptr1;

		return true;
	}

	void sort_bubble()
	{
		if (is_empty())
			return;

		int length = 0;
		int tmp = m_head;
		while (tmp != -1)
		{
			length++;
			tmp = m_data[tmp].next;
		}

		if (length < 2)
		{
			return;
		}

		bool sorted = false;

		int iterations = 0;
		while (!sorted)
		{
			sorted = true;

			int prev = -1;
			int iter = m_head;

			for (int i = 0; i < length - 1 - iterations; i++)
			{
				if (m_data[iter].info > m_data[m_data[iter].next].info)
				{
					swap_neighbour(prev);

					if (prev == -1)
					{
						prev = m_head;
					}
					else
					{
						prev = m_data[prev].next;
					}

					sorted = false;
					continue;
				}
				
				prev = iter;
				iter = m_data[iter].next;
			}
			iterations++;
		}
	}

	void print() const
	{
		int tmp = m_head;

		while (tmp != -1)
		{
			std::cout << m_data[tmp].info << " ";
			tmp = m_data[tmp].next;
		}

		std::cout << '\n';
	}

	// Prebaucje sve izmedju cvorova sa val1 i val2
	// na kraj bez cvorova val1 i val2
	void move_part_to_end(int val1, int val2)
	{
		int prev_start = -1;
		int tmp = m_head;

		int poz1 = 0;
		while (tmp != -1 && m_data[tmp].info != val1)
		{
			prev_start = tmp;
			tmp = m_data[tmp].next;
			poz1++;
		}
		int start = tmp;

		if (start == -1)
			return;

		tmp = m_head;
		int prev_end = -1;

		int poz2 = 0;
		while (tmp != - 1 && m_data[tmp].info != val2)
		{
			prev_end = tmp;
			tmp = m_data[tmp].next;
			poz2++;
		}

		int end = tmp;

		if (poz1 == poz2)
			return;

		// Ukoliko je cvor sa val2 pre cvora sa val1
		// menjamo start i end
		if (poz1 > poz2)
		{
			int pom = start;
			start = end;
			end = pom;
			prev_end = prev_start;
		}

		if (end == -1)
			return;

		while (tmp != -1 && m_data[tmp].next != -1)
		{
			tmp = m_data[tmp].next;
		}

		int tail = tmp;

		m_data[prev_end].next = -1;
		m_data[tail].next = m_data[start].next;
		m_data[start].next = end;
	}

	void update_at(int val, int add)
	{
		if (is_empty())
			return;


		int prev_iter = -1;
		int iter = m_head;

		while (iter != -1 && m_data[iter].info != val)
		{
			prev_iter = iter;
			iter = m_data[iter].next;
		}

		if (iter == -1)
			return;

		m_data[iter].info += add;

		int prev_updated = prev_iter;
		int updated = iter;

		prev_iter = iter;
		iter = m_data[iter].next;

		while (iter != -1 && m_data[iter].info < m_data[updated].info)
		{
			prev_iter = iter;
			iter = m_data[iter].next;
		}

		// iter je element ispred kog treba prebaciti update-ovani cvor

		if (updated == prev_iter)
			return;

		if (prev_updated != -1)
		{
			m_data[prev_updated].next = m_data[updated].next;
			m_data[updated].next = iter;
			m_data[prev_iter].next = updated;
		}
		else
		{
			int pom = m_head;
			m_head = m_data[m_head].next;
			m_data[pom].next = iter;
			m_data[prev_iter].next = pom;
		}
	}
	
	void fill_in_the_blanks()
	{
		if (is_empty())
			return;

		int iter = m_head;

		while (m_data[iter].next != -1)
		{
			if (m_data[m_data[iter].next].info == m_data[iter].info + 1)
			{
				iter = m_data[iter].next;
			}
			else if (m_data[m_data[iter].next].info == m_data[iter].info)
			{
				int deleted = m_data[iter].next;
				m_data[iter].next = m_data[m_data[iter].next].next;
				m_data[deleted].next = m_lrmp;
				m_lrmp = deleted;
			}
			else
			{
				int pom = m_lrmp;
				m_data[m_lrmp].info = m_data[iter].info + 1;
				m_lrmp = m_data[m_lrmp].next;
				m_data[pom].next = m_data[iter].next;
				m_data[iter].next = pom;
				iter = pom;
			}
		}

	}


};

