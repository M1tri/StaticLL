#pragma once
struct Node
{
	int info;
	int next;

	Node(int info = 0, int next = -1): info(info), next(next) {}
};

