/*
 * dynamicload.hxx
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

#ifndef IDT_DYNAMIC_LOAD_HXX
#define IDT_DYNAMIC_LOAD_HXX

extern "C" {
#include <dlfunctions.h>
#include <dlconfiguration.h>
}

#include <string>
#include <vector>
#include <map>

namespace dl {
    typedef std::string                 symbol_t; // type for names
    typedef std::vector<symbol_t>       symvec_t; // name container
    typedef std::map<symbol_t, dlptr_t> symmap_t; // name container

    /* Type used to pull out a library of functions from a module
     * 
     */

    class IDT_DL_API registry_t {
        symmap_t m_ptr; // container holding the function data
        
        public:
            registry_t() {}
            registry_t(symvec_t symvec_);
            
            symvec_t symbols; // the list of symbols to be parsed and loaded into the registry
        
            /* Insert a symbol into the map
            * @param symbol_ = the name of the function
            * @param data_   = the function data
            */
            void    insert(symbol_t symbol_, dlptr_t data_);
            void    insert(dlcstr_t symbol_, dlptr_t data_);

           /* Fast cast the symbol using these template functions
            * @param symbol_ = the symbol, of course
            * The function pointer submitted to fill the template
            *  must match the symbol's function exactly
            */
            template<typename T>
            T symbol_as(symbol_t symbol_) {
                 return (T)m_ptr.at(symbol_);
            }
    };

    typedef registry_t* (*dlget_t)(symvec_t&);

    class IDT_DL_API loader_t {
        dlhandle_t  m_handle;
        
        symbol_t m_module,
                    m_symbol { "dlget" };

        dword_t     m_mode { DL_LAZY };
        
        public:
            /* @param modName_ = path to .so or .dll
             * @param symbol_  = symbol to load from file
             * @param mode_    = load flag
             * Throws dl::load_exception and exits with EXIT_FAILURE if failure
             */
            loader_t(symbol_t modName_, symbol_t symbol_, dword_t mode_);
            loader_t(dlcstr_t modName_, dlcstr_t symbol_, dword_t mode_);
            loader_t(symbol_t modName_, symbol_t symbol_);
            loader_t(dlcstr_t modName_, dlcstr_t symbol_);
            loader_t(symbol_t modName_, dword_t mode_);
            loader_t(dlcstr_t modName_, dword_t mode_);
            loader_t(symbol_t modName_);
            loader_t(dlcstr_t modName_);
            ~loader_t();
            
            /* Open the module for dynamic loading 
             * Throws dl::load_exception and returns false if failure
             */
            bool        open();

            /* Load the symbol from the module
             * Throws dl::load_exception and returns nullptr if failure
             */
            dlptr_t     symbol();

            /* Load a library of symbols using a registry_t object
             * @param symreg_ = registry object to be loaded with contained symbols
             * Throws dl::load_exception and returns false if failure
             */
            bool        library(registry_t& symreg_);

            // Free and close the module
            void        close();

                template<typename T>
                T symbol_as()                 { return (T)symbol(); }
            
                template<typename T>
                T symbol_as(symbol_t symbol_) { return (T)dlsymbol(m_handle, symbol_.c_str()); }

                template<typename T>
                T symbol_as(dlcstr_t symbol_) { return (T)dlsymbol(m_handle, symbol_); }
    };
}

#endif
