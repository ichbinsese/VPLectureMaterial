

int gGlobalVar = 0x10;

void simpleFunctionWithoutParam(void)
{
	int var1 = 0xDEADBEEF;
	int var2 = 0xB16B00B5;

	int x = var1 + var2;

	// Do something with a global var
	gGlobalVar = gGlobalVar ^ x;
}

void simpleSecondCallLevel(int newVal)
{
	int a;
	int b;

	int res = (a + b) - newVal;

	simpleFunctionWithoutParam();
}

int simpleFunctionCallTree(int newVal, int key)
{
	int firstLevelResult = 0;

	simpleSecondCallLevel(newVal);
	
	return firstLevelResult;
}

int main()
{
	int mainResult = simpleFunctionCallTree(0xAB, 0xCD);
	return 0;
}
