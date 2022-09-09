/*
 * test1.c
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

#include <dlfunctions.h>
#include <stdio.h>

typedef void (*printsummin_fp)(const char*); // function pointer type definition

int main(int argc, char** argv) {
    dlhandle_t     handle      = NULL; // module handle
    printsummin_fp printsummin = NULL; // function pointer
    
    if (argc == 4) {
        // initialize the handle with a filepath and a flag
        handle = dlhandlex(argv[1], DL_LAZY);
        
        /* or without a flag, too. On unix, this will call with DL_LAZY,
         * call the below or the above function, both simultaniously on one 
         * object shouldn't really be done, behaviour undefined
         */

        // handle = dlhandle(argv[1]);

        // if the handle is NULL, print the resulting error and exit with error code
        if (!handle) {
            fprintf(stderr, "dlfunction error: %s: @ %p\n", dlerror(), handle);
            return 1;
        }

        // clear any errors, they don't matter. Or maybe they do, check them if you want
        dlerror();

        printsummin = (printsummin_fp)dlsymbol(handle, argv[2]);

        // if the symbol is NULL, print the resulting error and exit with error code
        if (!printsummin) {
            fprintf(stderr, "dlfunction error: %s: @ %p\n", dlerror(), handle);
            dlfree(handle);
            return 1;
        }

        // print version
        dlversion();
        
        // call funciton
        printsummin("\n");
        printsummin(argv[3]);
        printsummin("\n");

        // always free the handle
        if (dlfree(handle) != 0) {
            fprintf(stderr, "dlfunction error: %s: @ %p\n", dlerror(), handle);
            return 1;
        }
    }
    else {
        fprintf(stderr, "dlfunction error: argc %d not enough arguments! min 3\n", argc - 1);
    }
    return 0;
}
