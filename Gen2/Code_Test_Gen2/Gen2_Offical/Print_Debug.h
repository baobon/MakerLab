#ifndef __Print_Debug_H_

/*
   Debug
*/

/* Uncomment to enable printing out nice debug messages. */
#define DEBUG_GEN

#define DEBUG_PRINTER Serial /**< Define where debug output will be printed. */
/* Setup debug printing macros. */
#ifdef DEBUG_GEN
#define GEN_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define GEN_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define GEN_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
#define GEN_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif



#endif
