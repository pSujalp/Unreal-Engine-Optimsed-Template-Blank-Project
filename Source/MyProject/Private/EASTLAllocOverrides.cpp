// Simple EASTL operator new/delete overrides expected by EASTL's allocator
// These provide the placement/new overloads used in EASTL's allocator code
// (e.g. ::new(pName, flags, ...) char[n]) so that the linker can resolve
// those symbols. They allocate with malloc/posix_memalign and free with free().

#include <cstdlib>
#include <new>
#include <stddef.h>

// Non-throwing helper to allocate memory or throw bad_alloc on failure
static void* EASTL_Malloc(size_t size, size_t alignment = alignof(void*))
{
#if defined(_POSIX_C_SOURCE) || defined(__APPLE__)
    if (alignment <= alignof(void*))
    {
        void* p = std::malloc(size);
        if (!p) throw std::bad_alloc();
        return p;
    }
    else
    {
        void* p = nullptr;
        int res = posix_memalign(&p, alignment, size);
        if (res != 0 || !p) throw std::bad_alloc();
        return p;
    }
#else
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
#endif
}

// Placement/new overrides used by EASTL (debug/new name and flags parameters).
// Signatures intentionally match what EASTL expects (size_t, const char*, int, unsigned, const char*, int)
void* operator new[](size_t size, const char* /*pName*/, int /*flags*/, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/)
{
    return EASTL_Malloc(size);
}

void* operator new(size_t size, const char* /*pName*/, int /*flags*/, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/)
{
    return EASTL_Malloc(size);
}

void* operator new[](size_t size, size_t alignment, size_t /*offset*/, const char* /*pName*/, int /*flags*/, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/)
{
    return EASTL_Malloc(size, alignment);
}

void* operator new(size_t size, size_t alignment, size_t /*offset*/, const char* /*pName*/, int /*flags*/, unsigned /*debugFlags*/, const char* /*file*/, int /*line*/)
{
    return EASTL_Malloc(size, alignment);
}

// Note: we intentionally do NOT provide global operator delete/delete[] here
// because Unreal Engine already provides them. Defining them here causes
// duplicate symbol linker errors. Memory allocated above will be freed by
// the engine's delete handlers when appropriate.
