/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
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
#include "CEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ IEcoLab1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ IEcoLab1Ptr_t me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Побайтное копирование: copyByte
 * </сводка>
 *
 * <описание>
 *   Побайтное копирование elemSize байт из src в dest.
 *   Используется как универсальный способ копирования элементов
 *   произвольного типа.
 * </описание>
 *
 */
void copyByte(const char *src, char *dest, size_t elemSize) {
    const char *end = src + elemSize;
    while (src < end) {
        *(dest++) = *(src++);
    }
}

/*
 *
 * <сводка>
 *   next_power_of_two_size
 * </сводка>
 *
 * <описание>
 *   Возвращает наименьшую степень двойки, не меньшую чем n.
 * </описание>
 *
 */
static size_t next_power_of_two_size(size_t n) {
    size_t m = 1;
    while (m < n) m <<= 1;
    return m;
}

/*
 *
 * <сводка>
 *   bitonic_compare_and_swap
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
static void bitonic_compare_and_swap(char *base, size_t elemSize, size_t i, size_t j, int dir,
                                     int (__cdecl *compare)(const void *, const void *), char *tmp) {
    char *pi = base + i * elemSize;
    char *pj = base + j * elemSize;
    int cmp = compare((const void*)pi, (const void*)pj);

    if (dir == 1) { /* ascending */
        if (cmp > 0) {
            /* swap pi <-> pj using tmp */
            copyByte(pj, tmp, elemSize);
            copyByte(pi, pj, elemSize);
            copyByte(tmp, pi, elemSize);
        }
    } else { /* descending */
        if (cmp < 0) {
            copyByte(pj, tmp, elemSize);
            copyByte(pi, pj, elemSize);
            copyByte(tmp, pi, elemSize);
        }
    }
}

/*
 *
 * <сводка>
 *   bitonic_merge_recursive
 * </сводка>
 *
 * <описание>
 *   Рекурсивное битонное слияние (bitonic merge).
 *   Преобразует битонную последовательность длины cnt, начиная с позиции low,
 *   в отсортированную последовательность в направлении dir.
 * </описание>
 *
 */
static void bitonic_merge_recursive(char *base, size_t elemSize, size_t low, size_t cnt, int dir,
                                    int (__cdecl *compare)(const void *, const void *), char *tmp) {
    if (cnt > 1) {
        size_t k = cnt / 2;
        size_t i;
        for (i = low; i < low + k; ++i) {
            bitonic_compare_and_swap(base, elemSize, i, i + k, dir, compare, tmp);
        }
        bitonic_merge_recursive(base, elemSize, low, k, dir, compare, tmp);
        bitonic_merge_recursive(base, elemSize, low + k, k, dir, compare, tmp);
    }
}

/*
 *
 * <сводка>
 *   bitonic_sort_recursive
 * </сводка>
 *
 * <описание>
 *   Рекурсивная процедура построения битонной последовательности и её слияния.
 *   Для блока элементов длины cnt, начиная с low:
 *     - сортирует первую половину в порядке возрастания,
 *     - вторую половину в порядке убывания,
 *     - затем выполняет bitonic_merge_recursive для объединения в требуемом dir.
 * </описание>
 *
 */
static void bitonic_sort_recursive(char *base, size_t elemSize, size_t low, size_t cnt, int dir,
                                   int (__cdecl *compare)(const void *, const void *), char *tmp) {
    if (cnt > 1) {
        size_t k = cnt / 2;
        /* первая половина — ascending (1), вторая — descending (0) */
        bitonic_sort_recursive(base, elemSize, low, k, 1, compare, tmp);
        bitonic_sort_recursive(base, elemSize, low + k, k, 0, compare, tmp);
        bitonic_merge_recursive(base, elemSize, low, cnt, dir, compare, tmp);
    }
}

/*
 *
 * <сводка>
 *   remove_zero_padding_block
 * </сводка>
 *
 * <описание>
 * Удаляет добавленные при выравнивании нулевые (padding) элементы
 * из отсортированного массива, сдвигая оставшиеся значения влево.
 * </описание>
 *
 */
static void remove_zero_padding_block(char *buffer, size_t elemSize, size_t total, size_t len_pad) {
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
        copyByte(buffer + readPos * elemSize, buffer + writePos * elemSize, elemSize);
        ++readPos;
        ++writePos;
    }
}

/*
 *
 * <сводка>
 *   CEcoLab1_bitonicSort_generic
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
static int16_t CEcoLab1_bitonicSort_generic(/* in */ struct IEcoLab1* me,
                                            void *arrPrt, size_t arrSize, size_t elemSize,
                                            int (__cdecl *compare)(const void *, const void *),
                                            int ascending) {
    char *tmp = 0;
	char *buffer = 0;
	size_t m = 0, len_pad = 0;
	CEcoLab1* pCMe = (CEcoLab1*)me;

    if (me == 0 || arrPrt == 0 || compare == 0 || elemSize == 0) {
        return -1;
    }

    if (arrSize <= 1) return 0;

    /* временный буфер для обмена одного элемента */
    tmp = (char*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elemSize);
    if (!tmp) return -1;

    /* вычисляем m = next power of two */
    m = next_power_of_two_size(arrSize);
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
            copyByte(src + i * elemSize, buffer + i * elemSize, elemSize);
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
    bitonic_sort_recursive(buffer, elemSize, 0, m, ascending ? 1 : 0, compare, tmp);

    /* удаляем блок нулевого паддинга */
    if (len_pad > 0) {
        remove_zero_padding_block(buffer, elemSize, m, len_pad);
    }

    /* копируем обратно первые arrSize элементов */
    {
        size_t i;
        char *dst = (char*)arrPrt;
        for (i = 0; i < arrSize; ++i) {
            copyByte(buffer + i * elemSize, dst + i * elemSize, elemSize);
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
 *   CEcoLab1_bitonicSort_int
 * </сводка>
 *
 * <описание>
 *   Сортировка массива int с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 *   Возвращает 0 при успехе, -1 при ошибке.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_bitonicSort_int(/* in */ struct IEcoLab1* me, int *arr, size_t arrSize, int ascending) {
    return CEcoLab1_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(int), compare_int, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab1_bitonicSort_long
 * </сводка>
 *
 * <описание>
 *   Сортировка массива long с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_bitonicSort_long(/* in */ struct IEcoLab1* me, long *arr, size_t arrSize, int ascending) {
    return CEcoLab1_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(long), compare_long, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab1_bitonicSort_float
 * </сводка>
 *
 * <описание>
 *   Сортировка массива float с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_bitonicSort_float(/* in */ struct IEcoLab1* me, float *arr, size_t arrSize, int ascending) {
    return CEcoLab1_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(float), compare_float, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab1_bitonicSort_double
 * </сводка>
 *
 * <описание>
 *   Сортировка массива double с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_bitonicSort_double(/* in */ struct IEcoLab1* me, double *arr, size_t arrSize, int ascending) {
    return CEcoLab1_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(double), compare_double, ascending);
}

/*
 *
 * <сводка>
 *   CEcoLab1_bitonicSort_longdouble
 * </сводка>
 *
 * <описание>
 *   Сортировка массива long double с помощью битонной сортировки.
 *   ascending = 1 → по возрастанию; 0 → по убыванию.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_bitonicSort_longdouble(/* in */ struct IEcoLab1* me, long double *arr, size_t arrSize, int ascending) {
    return CEcoLab1_bitonicSort_generic(me, (void*)arr, arrSize, sizeof(long double), compare_longdouble, ascending);
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
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ IEcoLab1Ptr_t me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_bitonicSort_int,
	CEcoLab1_bitonicSort_long,
	CEcoLab1_bitonicSort_float,
	CEcoLab1_bitonicSort_double,
	CEcoLab1_bitonicSort_longdouble
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
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

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
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
