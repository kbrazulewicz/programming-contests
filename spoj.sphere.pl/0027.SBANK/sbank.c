#include <stdio.h>
#include <stdlib.h>

struct bank_account_t {
	char number[31 + 2];

	int control;
	int bankCode;
	int accountCode1;
	int accountCode2;
};

int ba_compare(const void* a, const void* b)
{
	struct bank_account_t* accountA = *((struct bank_account_t**) a);
	struct bank_account_t* accountB = *((struct bank_account_t**) b);

	if (accountA->control != accountB->control) {
		return accountA->control - accountB->control;
	}
	if (accountA->bankCode != accountB->bankCode) {
		return accountA->bankCode - accountB->bankCode;
	}
	if (accountA->accountCode1 != accountB->accountCode1) {
		return accountA->accountCode1 - accountB->accountCode1;
	}
	if (accountA->accountCode2 != accountB->accountCode2) {
		return accountA->accountCode2 - accountB->accountCode2;
	}

	return 0;
}

void ba_input(struct bank_account_t* account)
{
	int a, b, c, d;

	fgets(account->number, sizeof(account->number), stdin);
	account->number[sizeof(account->number) - 2] = '\0';

	sscanf(account->number, "%d %d %d %d %d %d", 
			&account->control,
			&account->bankCode,
			&a, &b, &c, &d);

	account->accountCode1 = a * 10000 + b;
	account->accountCode2 = c * 10000 + d;
}


struct bank_account_t  accountArray[100000];
struct bank_account_t* accountPtrArray[100000];


void doPrint(int n)
{
	int i, c = 1;

	for (i = 0; i < n; i++) {
		if ((i < n - 1) && !ba_compare(accountPtrArray + i, accountPtrArray + i + 1)) {
			c++;
		} else {
			printf("%s %d\n", accountPtrArray[i]->number, c);
			c = 1;
		}
	}
}

void doOperate()
{
	int n, i;
	scanf("%d\n", &n);

	for (i = 0; i < n; i++) {
		ba_input(accountArray + i);
		accountPtrArray[i] = accountArray + i;
	}

	qsort(accountPtrArray, n, sizeof(accountPtrArray[0]), ba_compare);

	doPrint(n);
}



int main()
{
	int t, ti;
	scanf("%d", &t);

	for (ti = 0; ti < t; ti++) {
		if (ti) puts("");
		doOperate(ti);
	}
	
	return 0;
}
