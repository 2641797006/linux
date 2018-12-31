#ifndef _IDCARD_H_
#define _IDCARD_H_

int IDcheck(const char* ID)
{
	int i, sum=0;
	char key[11]={'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
	int coef[17]={7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
	for(i=0;i<17;i++)
		sum+=(*ID++-'0')*coef[i];
	if(key[sum%11]==*ID)
		return 1;
	return 0;
}

#endif
