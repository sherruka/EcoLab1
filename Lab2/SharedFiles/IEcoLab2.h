/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab2
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB2_H__
#define __I_ECOLAB2_H__

#include "IEcoBase1.h"

/* IEcoLab2 IID = {B2C3D4E5-F607-48A9-90BC-DEF123456789} */
#ifndef __IID_IEcoLab2
static const UGUID IID_IEcoLab2 = {0x01, 0x10, {0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x48, 0xA9, 0x90, 0xBC, 0xDE, 0xF1, 0x23, 0x45, 0x67, 0x89}};
#endif /* __IID_IEcoLab2 */

typedef struct IEcoLab2* IEcoLab2Ptr_t;

typedef struct IEcoLab2VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoLab2Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoLab2Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoLab2Ptr_t me);

    /* IEcoLab2 */
    int16_t (ECOCALLMETHOD *CEcoLab2_bitonicSort_int)(/* in */ IEcoLab2Ptr_t me, int *arr, size_t arrSize, int ascending); 
	int16_t (ECOCALLMETHOD *CEcoLab2_bitonicSort_long)(/* in */ IEcoLab2Ptr_t me, long *arr, size_t arrSize, int ascending); 
	int16_t (ECOCALLMETHOD *CEcoLab2_bitonicSort_float)(/* in */ IEcoLab2Ptr_t me, float *arr, size_t arrSize, int ascending); 
	int16_t (ECOCALLMETHOD *CEcoLab2_bitonicSort_double)(/* in */ IEcoLab2Ptr_t me, double *arr, size_t arrSize, int ascending);
	int16_t (ECOCALLMETHOD *CEcoLab2_bitonicSort_longdouble)(/* in */ IEcoLab2Ptr_t me, long double *arr, size_t arrSize, int ascending);

} IEcoLab2VTbl, *IEcoLab2VTblPtr;

interface IEcoLab2 {
    struct IEcoLab2VTbl *pVTbl;
} IEcoLab2;


#endif /* __I_ECOLAB2_H__ */