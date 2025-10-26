﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB1_H__
#define __C_ECOLAB1_H__

#include "IEcoLab1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

typedef struct CEcoLab1 {
    /* Таблица функций интерфейса IEcoLab1 */
    IEcoLab1VTbl* m_pVTblIEcoLab1;

    /* Таблицы функций для интерфейсов IEcoCalculatorY и IEcoCalculatorX */
    IEcoCalculatorYVTbl* m_pVTblIY;
    IEcoCalculatorXVTbl* m_pVTblIX;

    /* Неделегирующий IEcoUnknown для поддержки агрегирования */
    IEcoUnknownVTbl* m_pVTblINondelegatingUnk;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

    /* Указатели на внутренние компоненты */
    IEcoCalculatorY* m_pIY_D;
    IEcoCalculatorY* m_pIY_E;
    IEcoUnknown* m_pInnerUnknown;
    IEcoCalculatorX* m_pIX_C;
    IEcoCalculatorX* m_pIX_A;
    IEcoUnknown* m_pIUnkOuter;

} CEcoLab1, *CEcoLab1Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1);

#endif /* __C_ECOLAB1_H__ */
