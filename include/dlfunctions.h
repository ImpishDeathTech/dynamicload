/*
 * dlfunctions.h
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

#ifndef IDT_DYNAMIC_LOAD_FUNCTIONS_H 
#define IDT_DYNAMIC_LOAD_FUNCTIONS_H

#include <dlconfiguration.h>

/* Load a shared object to a file handle
 * When the DL_FLAG macros are used on windows, they do absolutely nothing as of this moment
 * For windows flag usage : https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryexa
 * @param modName_  = the filepath to the module object to load
 * @param modeFlag_ = the flag determining how the file is handled by the operating system
 * @returns a handle to the object if sucessfully loaded, NULL if failure
 */
IDT_DL_API dlhandle_t dlhandlex(dlcstr_t modName_, dword_t modeFlag_);

/* Same ase dlhandlex(), but with modeFlag_ set to DL_LAZY on unix
 * @param modName_  = the filepath to the object
 * @returns a handle to the object if success, NULL if fail;
 */
IDT_DL_API dlhandle_t dlhandle(dlcstr_t modName_);

/* Get a symbol from the object
 * @param mod_ = the file handle to the object
 * @param sym_ = the name of the symbol
 * @returns a function pointer if success, NULL if fail
 *      note that the function pointer casted from this function must match the
 *      function definition type and arguments exactly
 *      if the definition is int somefunc(float), the pointer must in turn be of int (*)(float)
 */
IDT_DL_API dlptr_t    dlsymbol(dlhandle_t mod_, dlcstr_t sym_);

/* Get the most recent error in a nice, basic formatted error string
 * @returns a basic cstring containing the error
 */

#if defined(IDT_DYNAMIC_LOAD_WIN32)
IDT_DL_API dlcstr_t   dlerror(void);
#endif

/* Don't forget to free your module handle when you're finnished. This is C.
 *  @param mod_ = the module handle to be closed
 *  @returns 0 if usccess, or -1 if failure;
 */
IDT_DL_API int   dlfree(dlhandle_t mod_);

// print the version and copyright
IDT_DL_API void dlversion();

#endif // 1
