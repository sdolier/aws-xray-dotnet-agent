// Copyright (c) .NET Foundation and contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ClassFactory.h"
#include "CorProfiler.h"
#include "assert.h"

ClassFactory::ClassFactory() : refCount(1)
{
}

ClassFactory::~ClassFactory()
{
}

HRESULT STDMETHODCALLTYPE ClassFactory::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == IID_IUnknown || riid == IID_IClassFactory)
    {
        *ppvObject = this;
        this->AddRef();

        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE ClassFactory::AddRef()
{
    return ++this->refCount;
}

ULONG STDMETHODCALLTYPE ClassFactory::Release()
{
    int count = --this->refCount;
    if (count <= 0)
    {
        delete this;
    }

    return count;
}

HRESULT STDMETHODCALLTYPE ClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
{
    if (pUnkOuter != nullptr)
    {
        *ppvObject = nullptr;
        return CLASS_E_NOAGGREGATION;
    }

    CorProfiler* profiler = new CorProfiler();
    if (profiler == nullptr)
    {
        return E_FAIL;
    }

    assert(riid == __uuidof(ICorProfilerCallback8) ||
           riid == __uuidof(ICorProfilerCallback7) ||
           riid == __uuidof(ICorProfilerCallback6) ||
           riid == __uuidof(ICorProfilerCallback5) ||
           riid == __uuidof(ICorProfilerCallback4) ||
           riid == __uuidof(ICorProfilerCallback3) ||
           riid == __uuidof(ICorProfilerCallback2) ||
           riid == __uuidof(ICorProfilerCallback) ||
           riid == IID_IUnknown);

    return profiler->QueryInterface(riid, ppvObject);
}

HRESULT STDMETHODCALLTYPE ClassFactory::LockServer(BOOL fLock)
{
    return S_OK;
}
