#include <iostream>
#include <ctime>;
#include <iomanip>;

using namespace std;
struct node
{
	int index;
	bool visited = false;
	node* next;
};

void maps(bool seg_A[5][5], bool seg_B[5][5], bool seg_C[5][5], bool seg_D[5][5], bool seg_E[5][5], bool seg_F[5][5], int map[20][40]) {
	int losowa;
	srand(time(NULL));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			losowa = rand() % 6 + 1;
			for (int m = 0; m < 5; m++) {
				for (int n = 0; n < 5; n++) {
					switch (losowa) {
					case 1:
						map[m + i * 5][n + j * 5] = seg_A[m][n]; break;
					case 2:
						map[m + i * 5][n + j * 5] = seg_B[m][n]; break;           // losowanie mapy
					case 3:
						map[m + i * 5][n + j * 5] = seg_C[m][n]; break;
					case 4:
						map[m + i * 5][n + j * 5] = seg_D[m][n]; break;
					case 5:
						map[m + i * 5][n + j * 5] = seg_E[m][n]; break;
					case 6:
						map[m + i * 5][n + j * 5] = seg_F[m][n]; break;

					}
				}
			}
		}
	}
}

void start(int map[20][40], int& position_r, int& position_c) {
	bool pos = true;
	srand(time(NULL));
	while (pos) {
		position_r = rand() % 20;
		position_c = rand() % 40;
		if (map[position_r][position_c] == 1) {
			map[position_r][position_c] = 2;
			pos = false;
		}
	}                                                         //pozycja startowa
	pos = true;
	while (pos) {
		position_r = rand() % 20;
		position_c = rand() % 40;
		if (map[position_r][position_c] == 1) {
			map[position_r][position_c] = 3;
			pos = false;
		}
	}

}

void adjacency(node** list, int map[20][40]) {
	node* beg;
	node* b;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			if (map[i][j] >= 2)
			{
				b = new node;
				b->next = NULL;
				if ((map[i][j + 1] >= 2) && (j < 39))
				{
					beg = new node;
					beg->index = map[i][j + 1];
					beg->next = b->next;
					b->next = beg;
				}
				if ((j > 0) && (map[i][j - 1] >= 2))
				{
					beg = new node;
					beg->index = map[i][j - 1];                                         // tworzenie argumentow listy

					beg->next = b->next;
					b->next = beg;
				}
				if ((i > 0) && (map[i - 1][j] >= 2))
				{
					beg = new node;
					beg->index = map[i - 1][j];
					beg->next = b->next;
					b->next = beg;
				}
				if ((map[i + 1][j] >= 2) && (i < 19))
				{
					beg = new node;
					beg->index = map[i + 1][j];
					beg->next = b->next;
					b->next = beg;
				}
				list[map[i][j] - 2] = b;
			}
		}
	}
}

int DFS(node** list, int map[20][40], int nr = 2) {
	node* beg;
	beg = list[nr - 2];
	beg->visited = true;

	if (nr == 3) {
		return 1;
	}

	while (beg) {
		if (list[beg->index - 2]->visited != true) {   // sprawdzenie odwiedzenia
			nr = beg->index;
			if (DFS(list, map, nr) == 1) {
				if (nr != 3)
					for (int i = 0; i < 20; i++)
						for (int j = 0; j < 40; j++)  // tworzenie drogi AB
							if (map[i][j] == nr)
								map[i][j] = 1;

				return 1;
			}
		}
		else beg = beg->next;
	}
	return 0;
}

void delete_list(node** list, node*& beg, int white) {
	node* buf;
	for (int i = 0; i < white; i++) {
		beg = list[i];
		if (beg != NULL) {                  //usuwanie listy
			buf = beg;
			beg = beg->next;
			delete buf;
		}
	}
	delete[] list;
}

void mapchar(int map[20][40]) {

	for (int i = 0; i < 42; i++)
		cout << char(0xDB);
	cout << endl;
	for (int i = 0; i < 20; i++) {
		cout << char(0xDB);
		for (int j = 0; j < 40; j++) {      // wypisywanie mapy
			if (map[i][j] == 0)
				cout << char(0xDB);
			else if (map[i][j] == 1)
				cout << "x";
			else if (map[i][j] == 2)
				cout << "A";
			else if (map[i][j] == 3)
				cout << "B";
			else	cout << " ";
		}
		cout << char(0xDB);
		cout << endl;
	}
	for (int i = 0; i < 42; i++)
		cout << char(0xDB);
	cout << endl;
}

int main() {
	node** list;
	node* beg;
	beg = new node;
	beg = NULL;
	int position_r;
	int position_c;
	int map[20][40];
	bool seg_A[5][5] = { {0,0,1,0,0},{0,1,1,0,0},{1,1,0,1,1},{0,1,1,1,0},{0,0,1,0,0} };
	bool seg_B[5][5] = { {0,0,1,1,0},{1,0,0,1,0},{1,1,1,1,1},{0,1,1,1,0},{0,0,1,1,0} };
	bool seg_C[5][5] = { {1,1,1,1,1},{1,1,0,1,1},{1,1,0,0,1},{0,1,0,0,0},{0,1,1,1,1} };    //segmenty
	bool seg_D[5][5] = { {0,0,1,1,1},{0,1,1,0,1},{1,1,0,1,1},{1,0,1,1,0},{0,1,1,0,0} };
	bool seg_E[5][5] = { {1,1,1,0,0},{0,1,1,1,0},{1,1,0,1,1},{1,1,0,1,1},{1,1,1,1,0} };
	bool seg_F[5][5] = { {0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0} };
	maps(seg_A, seg_B, seg_C, seg_D, seg_E, seg_F, map);
	start(map, position_r, position_c);
	int white = 4;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			if (map[i][j] == 1) {
				map[i][j] = white;
				++white;
			}
		}
	}
	white -= 2;
	list = new node * [white];

	for (int i = 0; i < white; i++) {
		list[i] = 0;                        //lista
	}

	mapchar(map);
	adjacency(list, map);
	for (int i = 0; i < white; i++)
	{
		beg = list[i]->next;  // poprawa listy 
		list[i] = beg;
	}
	DFS(list, map);
	cout << endl << endl;
	mapchar(map);
	delete_list(list, beg, white);
}