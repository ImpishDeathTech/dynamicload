/*
 * dlconfiguration.h
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Christopher Stephen Rafuse
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef IDT_DYNAMIC_LOAD_CONFIGURATION_H
#define IDT_DYNAMIC_LOAD_CONFIGURATION_H

#define IDT_DYNAMIC_LOAD_VERSION_MAJOR 0
#define IDT_DYNAMIC_LOAD_VERSION_MINOR 5

#define IDT_DYNAMIC_LOAD_TESTING       true
#define IDT_DYNAMIC_LOAD_RELEASE       false


/* some definitions to make the c++ objects usable
 * from .dll or .so land
 */

typedef void* dlptr_t; // pointer type for raw data pointers produced by the dlsymbol function

// Unix Implementatioan
#if defined(__unix__)

    #if defined(__linux__) || defined(__ANDROID__) || defined(__FreeBSD__) || defined(__FreeBSD__kernel__)
        #define IDT_DYNAMIC_LOAD_UNIX
        #define IDT_DL_API __attribute__((__visibility__("default")))

        #include <dlfcn.h>
        #include <unistd.h>
        #include <stdint.h>

        #define DL_LAZY   RTLD_LAZY     // Realocations are preformed at an implementation-dependant time 
        #define DL_NOW    RTLD_NOW      // Realocations are preformed when the object is loaded
        #define DL_LOCAL  RTLD_LOCAL    // All symbols are not made available for realocation processing by other modules
        #define DL_GLOBAL RTLD_GLOBAL   // All symbols are made available for realocation processing by other modules

        typedef void*       dlhandle_t; // the module file handle
        typedef const char* dlcstr_t;   // a portable type definition of the cstring
        typedef uint32_t    dword_t;    // a portable type definition of a dword 

    #else
        #error dynamicload not implemented for this unix system
    #endif

// Windows implementation
#elif defined(_WIN32)
    #define IDT_DYNAMIC_LOAD_WIN32

    #include <Windows.h>

    // unix placeholders
    #define DL_LAZY   0x00000000
    #define DL_NOW    DL_LAZY
    #define DL_LOCAL  DL_LAZY
    #define DL_GLOBAL DL_LAZY

    // Windows portable of the above
    typedef HMODULE     dlhandle_t;
    typedef LPCSTR      dlcstr_t;
    typedef DWORD       dword_t;

    #if defined(DL_EXPORT)
        #define IDT_DL_API __declspec(dllexport)
    #else
        #define IDT_DL_API __declspec(dllimport)
    #endif

#else
    #error dynamicload not implemented for this operating system
#endif

#endif // IDT_DYNAMIC_LOAD_CONFIGURATION_H