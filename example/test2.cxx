/*
 * test1.cxx
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
#include <string>

typedef unsigned (*testtrunc_fp)(double);

int main(int argc, char** argv) {
    if (argc == 4) {
        try {
            std::stringstream ss(argv[3]);
            
            /* initialize the loader with a filepath and a symbol
             * this will call with DL_LAZY on unix
             */
            dl::loader_t      loader(argv[1], argv[2]);

            // set up the function pointer and argument
            testtrunc_fp      testtrunc = nullptr;
            double            target    = 0;
            ss >> target;

            // if loading the module fails, exit failure
            if (!loader.open())
                return EXIT_FAILURE;

            // example of symbol_as() method in action
            testtrunc = loader.symbol_as<testtrunc_fp>();

            std::cout << testtrunc(target) << std::endl;

            // free the module
            loader.close();
        }
        // catch the error and print it, if there is one
        catch (dl::loader_error& exn) {
            std::cerr << exn.what() << ": @ " << exn.at() << std::endl;
        }
    }
    else {
        std::cerr << argc - 1 << " invalid arg count! min 3\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}