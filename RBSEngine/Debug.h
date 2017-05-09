//usefull code supplyed in skydrive notes for printing out debug messages
// i learned a lot about preprocessor commands from it.
#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG 1
#if defined DEBUG
	#if (DEBUG == 1)
		#define DEBUG_MSG(x) (cout << (x) << endl)
	#else
		#define DEBUG_MSG(x)
	#endif
#else
	#define DEBUG_MSG(x)
#endif