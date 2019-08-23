#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[])
{
	int en;
	HANDLE hMapFile;
	LPVOID lpMapAddress;;
	
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
			FALSE,
			TEXT("SharedObject"));
			
	lpMapAddress = MapViewOfFile(hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0);
	int *p;
	p=(int *)lpMapAddress;
	for(en=0;en<100;en++){
//		printf("%d\n",a[en]);
		if(*(p+en*2)!=0)	
			printf("%ld.\n",*(p+en*2));
		else
			break;
	}

	
	UnmapViewOfFile(lpMapAddress);
	CloseHandle(hMapFile);
	system("pause");
}
