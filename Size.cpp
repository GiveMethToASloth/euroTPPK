#include <windows.h> 
#include <stdio.h> 
#include "EuroTPPK.h"
void size(void) 
{ char Buffer[200];
   // the files handle 
   HANDLE hFile1; 
   // the file is there... 
   LPCSTR fname1 = "houdini.dll"; 
 //  sprintf_s(mypath,"%s\\%s",szModulePath,cfgfile);
   // temporary storage for file sizes 
   DWORD dwFileSize; 
   DWORD dwFileType; 

   // Opening the existing file 
   hFile1 = CreateFile(fname1,     //file to open 
                GENERIC_READ,         //open for reading 
                FILE_SHARE_READ,      //share for reading 
                NULL,                 //default security 
                OPEN_EXISTING,        //existing file only 
                FILE_ATTRIBUTE_NORMAL, //normal file 
                NULL);                 //no attribute template 
  
   dwFileType = GetFileType(hFile1); 
   dwFileSize = GetFileSize(hFile1, NULL); 
 //  printf("%S size is %d bytes and file type is %d\n", fname1, dwFileSize, dwFileType); 
   sprintf_s(Buffer,"size is %S",dwFileSize);
	PrintMessage(Buffer,1);
   // Retrieve the file times for the file. 
   if(!GetFileTime(hFile1, &ftCreate, &ftAccess, &ftWrite)) 
   { 
	   PrintMessage("file opened not",1);
     //TerminateProcess(GetCurrentProcess(),0);
         return; 
   } 

   // Convert the created time to local time. 
   FileTimeToSystemTime(&ftCreate, &stUTC); 
      SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); 

   // Convert the last-access time to local time. 
   FileTimeToSystemTime(&ftAccess, &stUTC1); 
      SystemTimeToTzSpecificLocalTime(NULL, &stUTC1, &stLocal1); 

   // Convert the last-write time to local time. 
   FileTimeToSystemTime(&ftWrite, &stUTC2); 
      SystemTimeToTzSpecificLocalTime(NULL, &stUTC2, &stLocal2); 
    
   // Build a string showing the date and time. 
 //  printf("Created on: %02d/%02d/%d %02d:%02d\n", stLocal.wDay, stLocal.wMonth, 
//         stLocal.wYear, stLocal.wHour, stLocal.wMinute); 

 //  printf("Last accessed: %02d/%02d/%d %02d:%02d\n", stLocal1.wDay, stLocal1.wMonth, 
  //       stLocal1.wYear, stLocal1.wHour, stLocal1.wMinute); 

 //  printf("Last written: %02d/%02d/%d %02d:%02d\n", stLocal2.wDay, stLocal2.wMonth, 
  //       stLocal2.wYear, stLocal2.wHour, stLocal2.wMinute); 
   // close the file's handle and itself 
//   if(CloseHandle(hFile1) == 0) 
 //     printf("Can't close the %S handle!\n", fname1); 
 //  else 
 //     printf("%S handle closed successfully!\n", fname1); 
   return; 
}