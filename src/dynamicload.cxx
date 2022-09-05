/*
 * dynamicload.cxx
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

namespace dl {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // registry_t
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    registry_t::registry_t(symvec_t symvec_) {
        this->symbols = symvec_;
    }

    void registry_t::insert(symbol_t symbol_, dlptr_t data_) {
        if (m_ptr.find(symbol_) != m_ptr.end())
            throw loader_error(symbol_ + " already loaded: Can't load symbol twice", m_ptr.at(symbol_));
            
        else m_ptr[symbol_] = data_;
    }

    void registry_t::insert(dlcstr_t symbol_, dlptr_t data_) {
        symbol_t symbol(symbol_);
        this->insert(symbol, data_);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // loader_t implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    loader_t::loader_t(symbol_t modName_, symbol_t symbol_, dword_t mode_)
        : m_module(modName_), m_symbol(symbol_), m_mode(mode_)
    {}


    loader_t::loader_t(dlcstr_t modName_, dlcstr_t symbol_, dword_t mode_) 
        : m_module(modName_), m_symbol(symbol_), m_mode(mode_)
    {}


    loader_t::loader_t(symbol_t modName_, symbol_t symbol_)
        : m_module(modName_), m_symbol(symbol_)
    {}


    loader_t::loader_t(dlcstr_t modName_, dlcstr_t symbol_) 
        : m_module(modName_), m_symbol(symbol_)
    {}

    
    loader_t::loader_t(symbol_t modName_)
        : m_module(modName_)
    {}


    loader_t::loader_t(dlcstr_t modName_)
        : m_module(modName_)
    {}


    loader_t::~loader_t() {
        this->close();
    }


    bool loader_t::open() {
        m_handle = dlhandlex(m_module.c_str(), m_mode);

        if (!m_handle) {
            throw loader_error(dlgeterror());
            return false;
        }
        return true;
    }


    dlptr_t loader_t::symbol() {
        dlptr_t p = dlsymbol(m_handle, m_symbol.c_str());
        if (!p) {
            throw loader_error(dlgeterror(), m_handle);
            return nullptr;
        }
        return p;
    }


    bool loader_t::library(registry_t& symreg_) {
        for (std::vector<symbol_t>::iterator i = symreg_.symbols.begin(); i != symreg_.symbols.end(); ++i) {
            dlptr_t fp = dlsymbol(m_handle, (*i).c_str());
            if (!fp) {
                throw loader_error(dlgeterror(), m_handle);
                return false;
            }
            else symreg_.insert((*i), fp);
        }
        return true;
    }


    void loader_t::close() {
        if (m_handle) dlfree(m_handle);
    }
}