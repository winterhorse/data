/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef STRINGIFYMACROS_H
#define STRINGIFYMACROS_H

// Put name between ""
#define STR(s) #s

//Put expanded macro/define between ""
#define XSTR(s) STR(s)

// generate a filename from file_root and extension part
#define concat(name,ext) name.ext
#define plainConcat(a,b) a##b
#define kernelInfoConcat(a) plainConcat(_kernel_info_,a)

#ifdef __ARMV8
#define extKernelInfoDecl(a)
#else
#define extKernelInfoDecl(a) extern KERNEL_INFO kernelInfoConcat(a)
#endif

#define processDescConcat(a) plainConcat(a,_apu_process_desc)

#define identity(s) s

// put the filename between ""
#define str_header(name,ext) XSTR(concat(name,ext))

#if 0
#ifndef APEX2_EMULATE // to avoid the ifdefs all over the code
#define XREGISTER_ACF_KERNEL(Kernel)
#define REGISTER_PROCESS_TYPE(a, b)
#endif

#endif

#ifdef APEX2_EMULATE
//syntax sugar macros
#define REGISTER_ACF_KERNEL(METADATA, FUNCTION) (ACF_Kernel::RegisterPrototypeInDatabase(ACF_Kernel((METADATA), (void*)(FUNCTION))));
#define XREGISTER_ACF_KERNEL(Kernel) REGISTER_ACF_KERNEL(kernelInfoConcat(Kernel), Kernel)
#else 
#define XREGISTER_ACF_KERNEL(Kernel) GET_KERNEL_HANDLE(&kernelInfoConcat(Kernel), XSTR(Kernel));
#endif

#ifdef APEX2_EMULATE
//syntax sugar macros
#define REGISTER_ACF_KERNEL(METADATA, FUNCTION) (ACF_Kernel::RegisterPrototypeInDatabase(ACF_Kernel((METADATA), (void*)(FUNCTION))));
#define XREGISTER_ACF_KERNEL(Kernel) REGISTER_ACF_KERNEL(kernelInfoConcat(Kernel), Kernel)
//#else
#if 0
#define XREGISTER_ACF_KERNEL(Kernel) GET_KERNEL_HANDLE(&kernelInfoConcat(Kernel), XSTR(Kernel))
#endif

#endif

#endif /* STRINGIFYMACROS_H */

