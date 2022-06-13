// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MAZESOLVER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MAZESOLVER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MAZESOLVER_EXPORTS
#define MAZESOLVER_API __declspec(dllexport)
#else
#define MAZESOLVER_API __declspec(dllimport)
#endif

// This class is exported from the dll
class MAZESOLVER_API CMazeSolver {
public:
	CMazeSolver(void);
	// TODO: add your methods here.
};

extern MAZESOLVER_API int nCMazeSolver;

MAZESOLVER_API int fnCMazeSolver(void);

