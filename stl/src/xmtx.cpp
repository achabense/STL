// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// mutex support

#include "xmtx.hpp"

#include "awint.hpp"

_EXTERN_C_UNLESS_PURE

// Win32 critical sections are recursive

_MRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Mtxinit(_Rmtx* _Mtx) noexcept { // initialize mutex
    InitializeCriticalSectionEx(_Mtx, 4000, 0);
}

_MRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Mtxdst(_Rmtx* _Mtx) noexcept { // delete mutex
    DeleteCriticalSection(_Mtx);
}

_RELIABILITY_CONTRACT
_MRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Mtxlock(_Rmtx* _Mtx) noexcept { // lock mutex
#ifdef _M_CEE
    System::Threading::Thread::BeginThreadAffinity();
#endif
    EnterCriticalSection(_Mtx);
}

_RELIABILITY_CONTRACT
_MRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Mtxunlock(_Rmtx* _Mtx) noexcept { // unlock mutex
    LeaveCriticalSection(_Mtx);
#ifdef _M_CEE
    System::Threading::Thread::EndThreadAffinity();
#endif
}

_END_EXTERN_C_UNLESS_PURE
