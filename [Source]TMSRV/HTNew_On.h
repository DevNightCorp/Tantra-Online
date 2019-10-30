#ifdef HT_ACTIVATE_MEMORY_MANAGER

#define new              new( __FILE__, __LINE__ )
#define delete           (CHTMemoryManagerGlobal::HT_vSetOwner( __FILE__, __LINE__ ), HT_FALSE) ? CHTMemoryManagerGlobal::HT_vSetOwner( "", 0 ) : delete
#define malloc(sz)       CHTMemoryManagerGlobal::HT_pvAllocateMemory( __FILE__, __LINE__, sz, HT_MM_MALLOC )
//#define calloc(num, sz)  CHTMemoryManagerGlobal::HT_pvAllocateMemory( __FILE__, __LINE__, sz* num, HT_MM_CALLOC )
#define realloc(ptr, sz) CHTMemoryManagerGlobal::HT_pvAllocateMemory( __FILE__, __LINE__, sz, HT_MM_REALLOC, ptr )
#define free(sz)         CHTMemoryManagerGlobal::HT_vDeAllocateMemory( __FILE__, __LINE__, sz, HT_MM_FREE )

#endif // #ifdef HT_ACTIVATE_MEMORY_MANAGER