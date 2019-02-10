#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 8
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] =
{ {0,3,INF,INF,INF,INF,INF,12},
{3,0,8,INF,INF,INF,INF,10},
{INF,8,0,15,2,INF,INF,INF},
{INF,INF,15,0,INF,INF,INF,INF},
{INF,INF,2,INF,0,9,4,5},
{INF,INF,INF,INF,9,0,INF,INF},
{INF,INF,INF,INF,4,INF,0,6},
{14,10,INF,INF,5,INF,6,0} };

struct distance {
	int key;//���� �� ����
	int dist;
}dist_st[MAX_VERTICES];
int found[MAX_VERTICES];

void build_min_heap(void) {
	int i = 1;
	int length = MAX_VERTICES;
	int child, parent;
	int temp;

	while (i != length / 2) {

		parent = i;
		child = i * 2;
		if (dist_st[child - 1].dist > dist_st[child + 1 - 1].dist)//�� ���� �ڽ� ��� �� �� ���� �� ����
			child = child + 1;

		while ((dist_st[parent - 1].dist > dist_st[child - 1].dist)) {
			//key�� ���� ������ �ٲ��ش�.
			temp = dist_st[parent - 1].key;//�迭 �ùٸ��� ����� ���ؼ� ���� -1 ���ش�.
			dist_st[parent - 1].key = dist_st[child - 1].key;
			dist_st[child - 1].key = temp;

			parent = child;

			if (child > MAX_VERTICES)
				break;

			child = parent * 2;
			if (dist_st[child - 1].dist > dist_st[child + 1 - 1].dist)//�� ���� �ڽ� ��� �� �� ���� �� ����
				child = child + 1;
		}
		i++;
	}
}


int Extract_Min() {//���İ��� 0�� �� return �Ѵ�.
	int min;
	int i;
	for (i = 0; i < MAX_VERTICES; i++) {
		if (found[i] == FALSE) {//queue���� ���ŵ��� �ʰ� ���� ���� �ּ��� ��
			min = i;
			break;
		}
	}
	return min;
}


void Decrease_key_min_heap(int i, int key) {
	dist_st[i].dist = key;
	build_min_heap;
}

void shortest_path(int start, int n) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		dist_st[i].dist = weight[start][i];
		found[i] = FALSE;
	}

	build_min_heap();


	found[start] = TRUE;
	dist_st[start].dist = 0;
	for (i = 0; i < n - 2; i++) {
		u = Extract_Min;
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if (!found[w]) {
				if (dist_st[u].dist + weight[u][w] < dist_st[w].dist) {
					Decrease_key_min_heap(w, dist_st[u].dist + weight[u][w]);
				}
			}
		}
	}
}

int main() {
	shortest_path(0, MAX_VERTICES);
}

