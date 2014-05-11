#include <stdio.h>
#include <string.h>

char board[100001];


int main()
{
	int i, count, length, off;

	scanf("%d", &count);

	for (i = 0; i < count; i++) {
		scanf("%d ", &length);
		fread(board, length, 1, stdin);
		off = length;

		while(off && board[--off] != 'b');
		while(off && board[--off] != 'a');
		if (!off) {
			printf("%s\n", length % 2 ? "TAK" : "NIE");
		} else {
			printf("%s\n", (length - off) % 2 ? "NIE" : "TAK");
		}
	}
	
	return 0;
}
