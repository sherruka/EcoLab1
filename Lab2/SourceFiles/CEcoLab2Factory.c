/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab2Factory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab2.h"
#include "CEcoLab2Factory.h"

/* Функция QueryInterface */
static int16_t ECOCALLMETHOD CEcoLab2Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return ERR_ECO_SUCCESES;
}

/* Функция AddRef */
static uint32_t ECOCALLMETHOD CEcoLab2Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/* Функция Release */
static uint32_t ECOCALLMETHOD CEcoLab2Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    --pCMe->m_cRef;

    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoLab2Factory(&pCMe->m_VtblICF);
        return 0;
    }
    return pCMe->m_cRef;
}

/* Функция Init */
static int16_t ECOCALLMETHOD CEcoLab2Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

/* Функция Alloc */
static int16_t ECOCALLMETHOD CEcoLab2Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        return ERR_ECO_NOAGGREGATION;
    }

    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return result;
    }

    result = me->pVTbl->Init(me, pISystem, pIUnk);

    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/* Функция get_Name */
static char_t* ECOCALLMETHOD CEcoLab2Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Name;
}

/* Функция get_Version */
static char_t* ECOCALLMETHOD CEcoLab2Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Version;
}

/* Функция get_Manufacturer */
static char_t* ECOCALLMETHOD CEcoLab2Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoLab2Factory* pCMe = (CEcoLab2Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_xA1B2C3D4E5F647A890ABCDEF12345678FactoryVTbl = {
    CEcoLab2Factory_QueryInterface,
    CEcoLab2Factory_AddRef,
    CEcoLab2Factory_Release,
    CEcoLab2Factory_Alloc,
    CEcoLab2Factory_Init,
    CEcoLab2Factory_get_Name,
    CEcoLab2Factory_get_Version,
    CEcoLab2Factory_get_Manufacturer
};

/* Создание экземпляра фабрики */
CEcoLab2Factory g_xA1B2C3D4E5F647A890ABCDEF12345678Factory = {
    &g_xA1B2C3D4E5F647A890ABCDEF12345678FactoryVTbl,
    0,
    (CreateInstance)createCEcoLab2,
    (InitInstance)initCEcoLab2,
    "EcoLab2\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_xA1B2C3D4E5F647A890ABCDEF12345678Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_A1B2C3D4E5F647A890ABCDEF12345678 = (IEcoComponentFactory*)&g_xA1B2C3D4E5F647A890ABCDEF12345678Factory;
#endif