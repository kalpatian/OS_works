#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
	HANDLE hFile,hMapFile;
	LPVOID lpMapAddress;
	
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, //file handle
					NULL, //default security
					PAGE_READWRITE, //read/write access to mapped pages
					0, //map entire file
					100000,
					TEXT("SharedObject"));//named shared memory object
	lpMapAddress = MapViewOfFile(hMapFile, //mapped object handle
					FILE_MAP_ALL_ACCESS, //read/write access
					0,//mapped view of entire file
					0,
					0);
					
//write to shared memory		
	int x,i,en;
	int ini;
	long long int a[100];
	for(ini=0;ini<100;ini++){
		a[ini]=0;
	}
	a[0]=1;
	printf("please input a number to be the imformation of the Catalan!...\n");
	scanf("%d",&x);	

	for(i=1;i<x;i++){
			a[i]=a[i-1]*(4*i-2)/(i+1);
	}		
	memcpy(lpMapAddress,a,100);
	int *p;
	p=(int *)lpMapAddress;
//	printf("%d\n",a[0]);
//	for(en=0;en<100;en++){
//		printf("%d\n",a[en]);	
//		printf("%ld.\n",*(p+en*2));
//		printf("once\n");     for debug
//}

	printf("initializing sharing space successfully!...\n");
	system("pause");	
	UnmapViewOfFile(lpMapAddress);
	CloseHandle(hMapFile); 
	
}
