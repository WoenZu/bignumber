void reverse(int *destArr, int *sourceArr, int i)
{
	int j = 0;
	while(i > 0)
		destArr[j++] = sourceArr[--i];

}