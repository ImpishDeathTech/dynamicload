/*
 * test3.cxx
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

#include <dynamicload.hxx>
#include <dlexception.hxx>
#include <iostream>
#include <sstream>

// function pointer type definitions
typedef void (*testprint_fp)(const char*);
typedef void (*testprintint_fp)(int);
typedef unsigned (*testtrunc_fp)(double);

int main(int argc, char** argv) {
    if (argc == 7) {
        try {

            // load up the registry symbols
            dl::registry_t lib({
                argv[2],
                argv[4],
                argv[5]
            });

            // boot up the loader
            dl::loader_t      loader(argv[1], (DL_NOW | DL_NODELETE));
            
            // load in the number argument
            std::stringstream ss(argv[6]);
            double            target;
            ss >> target;

            // if loading the module fails, exit failure
            if (!loader.open())
                return EXIT_FAILURE;
            
            // if loading the library fails, exit failure
            else if (!loader.library(lib))
                return EXIT_FAILURE;
            
            loader.close();
            // call testprint()
            lib.symbol_as<testprint_fp>(argv[2])(argv[3]);
            std::cout << std::endl;

            /* call testprintint() and testtrunc() with symbol_as<T>(dlcstr_t);
             * functions can be called directly from the fast cast
             */
            lib.symbol_as<testprintint_fp>
                (argv[4])(
                    lib.symbol_as<testtrunc_fp>
                        (argv[5])(target)
                );
            std::cout << std::endl;
        }
        // catch the exception to get the resulting error
        catch (dl::loader_error& exn) {
            std::cerr << exn.what() << ": @ " << exn.at() << std::endl;
        }
    }
    else {
        std::cerr << argc - 1 << " invalid arg count: Min 6";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
