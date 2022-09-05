/*
 * dlexception.hxx
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

#ifndef IDT_DYNAMIC_LOADER_EXCEPTION_HXX
#define IDT_DYNAMIC_LOADER_EXCEPTION_HXX
#include <exception>

extern "C" {
#include <dlfunctions.h>
#include <dlconfiguration.h>
}

namespace dl {
    
    /* For handling dynamicload errors in c++
     * what() = the error message
     * at()   = the handle address
     */
    class IDT_DL_API loader_error
        : public std::exception
    {
        std::string m_what { "[dynamicload] { ERROR } -> " };
        void*       m_at   { nullptr };

        public:
            // use if you just have an error message to send
            loader_error(std::string what_) {
                m_what += what_;
            }
            
            // use if you have the handle position or some data pointer to send
            loader_error(std::string what_, void* at_) 
                : m_at(at_)
            {
                m_what += what_;
            }

            loader_error(const char* what_) {
                m_what += what_;
            }

            loader_error(const char* what_, void* at_) 
                : m_at(at_)
            {
                m_what += what_;
            }

            virtual const char* what() const noexcept {
                return m_what.c_str();
            }

            virtual const void* at() const noexcept {
                return m_at;
            }
    };
}

#endif 