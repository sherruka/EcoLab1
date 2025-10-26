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
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab2.h"
#include "IdEcoCalculatorD.h"  // CID компонента D
#include "IdEcoCalculatorE.h"  // CID компонента E
#include "IdEcoCalculatorC.h"  // CID компонента C
#include "IdEcoCalculatorB.h"  // CID компонента B
#include "IdEcoCalculatorA.h"  // CID компонента A
#include "IdEcoLab1.h"  // CID компонента EcoLab1

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab2
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab2_QueryInterface(/* in */ IEcoLab2Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
	IEcoUnknown* nonDelegating = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Делегируем запрос неделегирующему Unknown */
    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    
    /* Если не нашли и есть внешний компонент - спрашиваем у него */
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    
    return result;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab2
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab2_AddRef(/* in */ IEcoLab2Ptr_t me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

	/* Делегируем неделегирующему Unknown */
    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab2
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab2_Release(/* in */ IEcoLab2Ptr_t me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

	/* Делегируем неделегирующему Unknown */
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

// QueryInterface для IEcoCalculatorY
int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_QueryInterface(struct IEcoCalculatorY* me, const UGUID* riid, void** ppv) {
    // Получаем указатель на CEcoLab2 через смещение
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    IEcoUnknown* nonDelegate = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;
    
    if (me == 0 || ppv == 0) return -1;
    
    result = nonDelegate->pVTbl->QueryInterface(nonDelegate, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_AddRef(struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    if (me == 0) return -1;
    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorY_Release(struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    if (me == 0) return -1;
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

// Умножение - вызываем внутренний компонент D
int32_t ECOCALLMETHOD CEcoLab2_Multiplication(struct IEcoCalculatorY* me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int32_t result = 0;
    
    if (me == 0) return -1;
    
    // Вызываем метод внутреннего компонента (включение)
    if (pCMe->m_pIY_D != 0) {
        result = pCMe->m_pIY_D->pVTbl->Multiplication(pCMe->m_pIY_D, a, b);
    }
    
    return result;
}

// Деление - вызываем внутренний компонент E
int16_t ECOCALLMETHOD CEcoLab2_Division(struct IEcoCalculatorY* me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int16_t result = 0;
    
    if (me == 0) return -1;
    
    if (pCMe->m_pIY_E != 0) {
        result = pCMe->m_pIY_E->pVTbl->Division(pCMe->m_pIY_E, a, b);
    }
    
    return result;
}

int16_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_QueryInterface(struct IEcoCalculatorX* me, const UGUID* riid, void** ppv) {
    // Смещение учитывает два предыдущих указателя
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*));
    IEcoUnknown* nonDelegate = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;
    int16_t result;
    
    if (me == 0 || ppv == 0) return -1;
    
    result = nonDelegate->pVTbl->QueryInterface(nonDelegate, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_AddRef(struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*));
    if (me == 0) return -1;
    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab2_IEcoCalculatorX_Release(struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*));
    if (me == 0) return -1;
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk);
}

// Сложение - вызываем внутренний компонент A 
int32_t ECOCALLMETHOD CEcoLab2_Addition(struct IEcoCalculatorX* me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*));
    int32_t result = 0;
    
    if (me == 0) return -1;
    
    if (pCMe->m_pIX_A != 0) {
        result = pCMe->m_pIX_A->pVTbl->Addition(pCMe->m_pIX_A, a, b);
    }
    
    return result;
}

// Вычитание - вызываем внутренний компонент C
int16_t ECOCALLMETHOD CEcoLab2_Subtraction(struct IEcoCalculatorX* me, int16_t a, int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*));
    int16_t result = 0;
    
    if (me == 0) return -1;
    
    if (pCMe->m_pIX_C != 0) {
        result = pCMe->m_pIX_C->pVTbl->Subtraction(pCMe->m_pIX_C, a, b);
    }
    
    return result;
}

// Неделегирующий QueryInterface
int16_t ECOCALLMETHOD CEcoLab2_NondelegatingQueryInterface(struct IEcoUnknown* me, const UGUID* riid, void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    int16_t result;
    
    if (me == 0 || ppv == 0) return -1;
    
    if (IsEqualUGUID(riid, &IID_IEcoLab2)) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        ++pCMe->m_cRef;
    }
	else if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
		// АГРЕГИРОВАНИЕ: если есть внутренний компонент EcoLab1 - передаем запрос ему
		if (pCMe->m_pInnerUnknownLab1 != 0) {
            result = pCMe->m_pInnerUnknownLab1->pVTbl->QueryInterface(
                pCMe->m_pInnerUnknownLab1, riid, ppv);
            return result;
        }
        else {
            *ppv = 0;
            return -1;
        }
	}
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        // АГРЕГИРОВАНИЕ: если есть внутренний компонент B - передаем запрос ему
        if (pCMe->m_pInnerUnknown != 0) {
            result = pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
			*ppv = &pCMe->m_pVTblIX;
			pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
		}
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
		*ppv = &pCMe->m_pVTblIY;
		pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

uint32_t ECOCALLMETHOD CEcoLab2_NondelegatingAddRef(struct IEcoUnknown* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    if (me == 0) return -1;
    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD CEcoLab2_NondelegatingRelease(struct IEcoUnknown* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*) - sizeof(struct IEcoCalculatorY*) - sizeof(struct IEcoCalculatorX*));
    
    if (me == 0) return -1;
    
    --pCMe->m_cRef;
    
    if (pCMe->m_cRef == 0) {
        // Освобождаем агрегированный компонент
        if (pCMe->m_pInnerUnknown != 0) {
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            } else {
                pCMe->m_cRef = 1;
            }
        }
		if (pCMe->m_pInnerUnknownLab1 != 0) {
            if (pCMe->m_pInnerUnknownLab1->pVTbl->Release(pCMe->m_pInnerUnknownLab1) == 0) {
                pCMe->m_pInnerUnknownLab1 = 0;
            } else {
                pCMe->m_cRef = 1;
            }
        }
        if (pCMe->m_cRef == 0) {
            deleteCEcoLab2((IEcoLab2*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Побайтное копирование: copyByteLab2
 * </сводка>
 *
 * <описание>
 *   Побайтное копирование elemSize байт из src в dest.
 *   Используется как универсальный способ копирования элементов
 *   произвольного типа.
 * </описание>
 *
 */
void copyByteLab2(const char *src, char *dest, size_t elemSize) {
    const char *end = src + elemSize;
    while (src < end) {
        *(dest++) = *(src++);
    }
}

/*
 *
 * <сводка>
 *   next_power_of_two_size_Lab2
 * </сводка>
 *
 * <описание>
 *   Возвращает наименьшую степень двойки, не меньшую чем n.
 * </описание>
 *
 */
static size_t next_power_of_two_size_Lab2(size_t n) {
    size_t m = 1;
    while (m < n) m <<= 1;
    return m;
}

/*
 *
 * <сводка>
 *   bitonic_compare_and_swap_Lab2
 * </сводка>
 *
 * <описание>
 *   Сравнивает элементы массива с индексами i и j с помощью
 *   пользовательской функции compare и при необходимости меняет
 *   их местами в зависимости от направления dir.
 *
 *   dir == 1  -> требуется возрастание (ascending)
 *   dir == 0  -> требуется убывание (descending)
 * </описание>
 *
 */
static void bitonic_compare_and_swap_Lab2(char *base, size_t elemSize, size_t i, size_t j, int dir,
                                     int (__cdecl *compare)(const void *, const void *), char *tmp) {
    char *pi = base + i * elemSize;
    char *pj = base + j * elemSize;
    int cmp = compare((const void*)pi, (const void*)pj);

    if (dir == 1) { /* ascending */
        if (cmp > 0) {
            /* swap pi <-> pj using tmp */
            copyByteLab2(pj, tmp, elemSize);
            copyByteLab2(pi, pj, elemSize);
            copyByteLab2(tmp, pi, elemSize);
        }
    } else { /* descending */
        if (cmp < 0) {
            copyByteLab2(pj, tmp, elemSize);
            copyByteLab2(pi, pj, elemSize);
            copyByteLab2(tmp, pi, elemSize);
        }
    }
}

/*
 *
 * <сводка>
 *   bitonic_merge_recursive_Lab2
 * </сводка>
 *
 * <описание>
 *   Рекурсивное битонное слияние (bitonic merge).
 *   Преобразует битонную последовательность длины cnt, начиная с позиции low,
 *   в отсортированную последовательность в направлении dir.
 * </описание>
 *
 */
static void bitonic_merge_recursive_Lab2(char *base, size_t elemSize, size_t low, size_t cnt, int dir,
                                    int (__cdecl *compare)(const void *, const void *), char *tmp) {
    if (cnt > 1) {
        size_t k = cnt / 2;
        size_t i;
        for (i = low; i < low + k; ++i) {
            bitonic_compare_and_swap_Lab2(base, elemSize, i, i + k, dir, compare, tmp);
        }
        bitonic_merge_recursive_Lab2(base, elemSize, low, k, dir, compare, tmp);
        bitonic_merge_recursive_Lab2(base, elemSize, low + k, k, dir, compare, tmp);
    }
}

/*
 *
 * <сводка>
 *   bitonic_sort_recursive_Lab2
 * </сводка>
 *
 * <описание>
 *   Рекурсивная процедура построения битонной последовательности и её слияния.
 *   Для блока элементов длины cnt, начиная с low:
 *     - сортирует первую половину в порядке возрастания,
 *     - вторую половину в порядке убывания,
 *     - затем выполняет bitonic_merge_recursive_Lab2 для объединения в требуемом dir.
 * </описание>
 *
 */
static void bitonic_sort_recursive_Lab2(char *base, size_t elemSize, size_t low, size_t cnt, int dir,
                                   int (__cdecl *compare)(const void *, const void *), char *tmp) {
    if (cnt > 1) {
        size_t k = cnt / 2;
        /* первая половина — ascending (1), вторая — descending (0) */
        bitonic_sort_recursive_Lab2(base, elemSize, low, k, 1, compare, tmp);
        bitonic_sort_recursive_Lab2(base, elemSize, low + k, k, 0, compare, tmp);
        bitonic_merge_recursive_Lab2(base, elemSize, low, cnt, dir, compare, tmp);
    }
}

/*
 *
 * <сводка>
 *   remove_zero_padding_block_Lab2
 * </сводка>
 *
 * <описание>
 * Удаляет добавленные при выравнивании нулевые (padding) элементы
 * из отсортированного массива, сдвигая оставшиеся значения влево.
 * </описание>
 *
 */
static void remove_zero_padding_block_Lab2(char *buffer, size_t elemSize, size_t total, size_t len_pad) {
    size_t i = 0, readPos = 0, writePos = 0;
	if (len_pad == 0) return;

    /* Найти первый индекс i, где элемент == 0 (все байты нуля) */
    for (; i < total; ++i) {
        int isZero = 1;
        size_t b;
        char *elem = buffer + i * elemSize;
        for (b = 0; b < elemSize; ++b) {
            if (elem[b] != 0) {
                isZero = 0;
                break;
            }
        }
        if (isZero) break;
    }

    /* Защита: если нулей нет, ничего не делаем */
    if (i == total) return;

    /* Удаляем padding элементы */
    readPos = i + len_pad;
    writePos = i;
    while (readPos < total) {
        copyByteLab2(buffer + readPos * elemSize, buffer + writePos * elemSize, elemSize);
        ++readPos;
        ++writePos;
    }
}

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_generic
 * </сводка>
 *
 * <описание>
 *   Универсальная битонная сортировка для массива произвольного типа.
 *   - arrPrt: указатель на массив;
 *   - arrSize: количество реальных элементов;
 *   - elemSize: размер одного элемента в байтах;
 *   - compare: функция сравнения;
 *   - ascending: 1 — сортировать по возрастанию, 0 — по убыванию.
 *
 *   Возвращаемые значения:
 *     0  — успех;
 *    -1  — ошибка (некорректные аргументы или ошибки выделения памяти).
 * </описание>
 *
 */
static int16_t CEcoLab2_bitonicSort_generic(/* in */ struct IEcoLab2* me,
                                            void *arrPrt, size_t arrSize, size_t elemSize,
                                            int (__cdecl *compare)(const void *, const void *),
                                            int ascending) {
    char *tmp = 0;
	char *buffer = 0;
	size_t m = 0, len_pad = 0;
	CEcoLab2* pCMe = (CEcoLab2*)me;

    if (me == 0 || arrPrt == 0 || compare == 0 || elemSize == 0) {
        return -1;
    }

    if (arrSize <= 1) return 0;

    /* временный буфер для обмена одного элемента */
    tmp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elemSize);
    if (!tmp) return -1;

    /* вычисляем m = next power of two */
    m = next_power_of_two_size_Lab2(arrSize);
    len_pad = m - arrSize;

    buffer = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, m * elemSize);
    if (!buffer) {
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tmp);
        return -1;
    }

    /* копируем реальные элементы */
    {
        size_t i;
        char *src = (char*)arrPrt;
        for (i = 0; i < arrSize; ++i) {
            copyByteLab2(src + i * elemSize, buffer + i * elemSize, elemSize);
        }
    }

    /* паддинг нулями */
    if (len_pad > 0) {
        size_t i;
        for (i = arrSize; i < m; ++i) {
            char *dst = buffer + i * elemSize;
            size_t j;
            for (j = 0; j < elemSize; ++j) dst[j] = 0;
        }
    }

    /* сортируем (ascending: dir = 1, descending: dir = 0) */
    bitonic_sort_recursive_Lab2(buffer, elemSize, 0, m, ascending ? 1 : 0, compare, tmp);

    /* удаляем блок нулевого паддинга */
    if (len_pad > 0) {
        remove_zero_padding_block_Lab2(buffer, elemSize, m, len_pad);
    }

    /* копируем обратно первые arrSize элементов */
    {
        size_t i;
        char *dst = (char*)arrPrt;
        for (i = 0; i < arrSize; ++i) {
            copyByteLab2(buffer + i * elemSize, dst + i * elemSize, elemSize);
        }
    }

    /* освобождаем буферы */
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, buffer);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, tmp);

    return 0;
}

/* -------------------- Typed comparator functions -------------------- */

static int __cdecl compare_int(const void *a, const void *b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int __cdecl compare_long(const void *a, const void *b) {
    long va = *(const long*)a;
    long vb = *(const long*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int __cdecl compare_float(const void *a, const void *b) {
    float va = *(const float*)a;
    float vb = *(const float*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int __cdecl compare_double(const void *a, const void *b) {
    double va = *(const double*)a;
    double vb = *(const double*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

static int __cdecl compare_longdouble(const void *a, const void *b) {
    long double va = *(const long double*)a;
    long double vb = *(const long double*)b;
    if (va < vb) return -1;
    if (va > vb) return 1;
    return 0;
}

/* -------------------- Typed wrapper functions (интерфейсные методы) -------------------- */

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_int
 * </сводка>
 *
 * <описание>
 *   Сортировка массива int с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 *   Возвращает 0 при успехе, -1 при ошибке.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_bitonicSort_int(/* in */ struct IEcoLab2* me, int *arr, size_t arrSize, int ascending) {
    return CEcoLab2_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(int), compare_int, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_long
 * </сводка>
 *
 * <описание>
 *   Сортировка массива long с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_bitonicSort_long(/* in */ struct IEcoLab2* me, long *arr, size_t arrSize, int ascending) {
    return CEcoLab2_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(long), compare_long, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_float
 * </сводка>
 *
 * <описание>
 *   Сортировка массива float с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_bitonicSort_float(/* in */ struct IEcoLab2* me, float *arr, size_t arrSize, int ascending) {
    return CEcoLab2_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(float), compare_float, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_double
 * </сводка>
 *
 * <описание>
 *   Сортировка массива double с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_bitonicSort_double(/* in */ struct IEcoLab2* me, double *arr, size_t arrSize, int ascending) {
    return CEcoLab2_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(double), compare_double, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab2_bitonicSort_longdouble
 * </сводка>
 *
 * <описание>
 *   Сортировка массива long double с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_bitonicSort_longdouble(/* in */ struct IEcoLab2* me, long double *arr, size_t arrSize, int ascending) {
    return CEcoLab2_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(long double), compare_longdouble, ascending);
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ IEcoLab2Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoInterfaceBus1* pIBus = 0;
	IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me;	
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
	if (result != 0 || pIBus == 0) return result;

	/* Проверка указателей */
	if (me == 0 ) {
		return result;
	}

	/* Сохранение указателя на системный интерфейс */
	pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

	// Получаем компонент A IEcoCalculatorX (ВКЛЮЧЕНИЕ)
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX_A);
	if (result != 0) pCMe->m_pIX_A = 0;

	// Пытаемся АГРЕГИРОВАТЬ компонент B для IEcoCalculatorX
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknown);
	if (result != 0) pCMe->m_pInnerUnknown = 0;

	// Пытаемся АГРЕГИРОВАТЬ компонент Eco.Lab1
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, pOuterUnknown, &IID_IEcoUnknown, (void**)&pCMe->m_pInnerUnknownLab1);
	if (result != 0) pCMe->m_pInnerUnknownLab1 = 0;

	// Получаем компонент C IEcoCalculatorX (ВКЛЮЧЕНИЕ)
	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorX, (void**)&pCMe->m_pIX_C);
	if (result != 0) pCMe->m_pIX_C = 0;

	// Получаем компонент D IEcoCalculatorY (ВКЛЮЧЕНИЕ)
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY_D);
	if (result != 0) pCMe->m_pIY_D = 0;

	// Получаем компонент E IEcoCalculatorY (ВКЛЮЧЕНИЕ)
	result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**)&pCMe->m_pIY_E);
	if (result != 0) pCMe->m_pIY_E = 0;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab2 */
IEcoLab2VTbl g_vtbl_IEcoLab2 = {
    CEcoLab2_QueryInterface,
    CEcoLab2_AddRef,
    CEcoLab2_Release,
    CEcoLab2_bitonicSort_int,
    CEcoLab2_bitonicSort_long,
    CEcoLab2_bitonicSort_float,
    CEcoLab2_bitonicSort_double,
    CEcoLab2_bitonicSort_longdouble
};

// Таблица для IEcoCalculatorY
IEcoCalculatorYVTbl g_vtbl_IEcoCalculatorY_Lab2 = {
    CEcoLab2_IEcoCalculatorY_QueryInterface,
    CEcoLab2_IEcoCalculatorY_AddRef,
    CEcoLab2_IEcoCalculatorY_Release,
    CEcoLab2_Multiplication,
    CEcoLab2_Division
};

// Таблица для IEcoCalculatorX
IEcoCalculatorXVTbl g_vtbl_IEcoCalculatorX_Lab2 = {
    CEcoLab2_IEcoCalculatorX_QueryInterface,
    CEcoLab2_IEcoCalculatorX_AddRef,
    CEcoLab2_IEcoCalculatorX_Release,
    CEcoLab2_Addition,
    CEcoLab2_Subtraction
};

// Таблица для неделегирующего IEcoUnknown
IEcoUnknownVTbl g_vtbl_IEcoUnknown_Lab2 = {
    CEcoLab2_NondelegatingQueryInterface,
    CEcoLab2_NondelegatingAddRef,
    CEcoLab2_NondelegatingRelease
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab2 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab2 */
    pCMe->m_pVTblIEcoLab2 = &g_vtbl_IEcoLab2 ;

	// Инициализируем новые таблицы
	pCMe->m_pVTblIY = &g_vtbl_IEcoCalculatorY_Lab2 ;
	pCMe->m_pVTblIX = &g_vtbl_IEcoCalculatorX_Lab2 ;
	pCMe->m_pVTblINondelegatingUnk = &g_vtbl_IEcoUnknown_Lab2;

	// Настраиваем поддержку агрегирования 
	pCMe->m_pIUnkOuter = 0;
	if (pIUnkOuter != 0) {
		pCMe->m_pIUnkOuter = pIUnkOuter;  // Если нас агрегируют
	} else {
		pCMe->m_pIUnkOuter = (IEcoUnknown*)&pCMe->m_pVTblINondelegatingUnk;  // Иначе указываем на себя
	}

	// Инициализируем указатели на внутренние компоненты
	pCMe->m_pIX_A = 0;
	pCMe->m_pInnerUnknown = 0;
	pCMe->m_pIX_C = 0;
	pCMe->m_pIY_D = 0;
	pCMe->m_pIY_E = 0;
	pCMe->m_pInnerUnknownLab1 = 0;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab2 = (IEcoLab2*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoLab2;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab2 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
		if ( pCMe->m_pIX_A != 0 ) {
			pCMe->m_pIX_A->pVTbl->Release(pCMe->m_pIX_A);
		}
		if ( pCMe->m_pInnerUnknown != 0 ) {
			pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown);
		}
		if ( pCMe->m_pIX_C != 0 ) {
			pCMe->m_pIX_C->pVTbl->Release(pCMe->m_pIX_C);
		}
		if ( pCMe->m_pIY_D != 0 ) {
			pCMe->m_pIY_D->pVTbl->Release(pCMe->m_pIY_D);
		}
		if ( pCMe->m_pIY_E != 0 ) {
			pCMe->m_pIY_E->pVTbl->Release(pCMe->m_pIY_E);
		}
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
		if ( pCMe->m_pInnerUnknownLab1 != 0 ) {
			pCMe->m_pInnerUnknownLab1->pVTbl->Release(pCMe->m_pInnerUnknownLab1);
		}
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}