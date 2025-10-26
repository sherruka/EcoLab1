/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoLab2.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoCalculatorY.h"  // Интерфейс для умножения/деления
#include "IEcoCalculatorX.h"  // Интерфейс для сложения/вычитания

typedef struct CEcoLab2 {

    /* Таблица функций интерфейса IEcoLab2 */
    IEcoLab2VTbl* m_pVTblIEcoLab2;

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
	IEcoUnknown* m_pInnerUnknownLab1;   // Для агрегирования Eco.Lab1
    IEcoCalculatorY* m_pIY_D;           // Для включения D
	IEcoCalculatorY* m_pIY_E;           // Для включения E
    IEcoUnknown* m_pInnerUnknown;       // Для агрегирования B
	IEcoCalculatorX* m_pIX_C;           // Для включения C c интерфейсом X
    IEcoCalculatorX* m_pIX_A;           // Для включения A
    IEcoUnknown* m_pIUnkOuter;          // Внешний Unknown (для агрегирования)

} CEcoLab2, *CEcoLab2Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoLab2* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2);

#endif /* __C_ECOLAB2_H__ */