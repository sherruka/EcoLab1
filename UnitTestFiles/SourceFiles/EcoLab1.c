/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

/*
 *
 * <сводка>
 *   my_rand
 * </сводка>
 *
 * <описание>
 *   Генерирует псевдослучайное число uint32_t.
 * </описание>
 *
 */
static uint32_t lcg_seed = 123456789;

static uint32_t my_rand() {
    lcg_seed = 1664525 * lcg_seed + 1013904223;
    return lcg_seed;
}

/*
 *
 * <сводка>
 *   copy_array
 * </сводка>
 *
 * <описание>
 *   Копирует массив произвольного типа.
 * </описание>
 *
 */
static void copy_array(void *dst, void *src, size_t elemSize, size_t n) {
    char *d = (char*)dst;
    char *s = (char*)src;
	size_t i = 0, b = 0;
    for (i = 0; i < n; i++) {
        for (b = 0; b < elemSize; b++)
            d[i*elemSize + b] = s[i*elemSize + b];
    }
}

/*
 *
 * <сводка>
 *   fill_int_array
 * </сводка>
 *
 * <описание>
 *   Заполняет массив int случайными числами.
 * </описание>
 *
 */
static void fill_int_array(int *arr, size_t n, int bigNumbers) {
	size_t i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = bigNumbers ? (int)(my_rand() % 2000000000 - 1000000000) : (int)(my_rand() % 100 - 50);
    }
}

/* --- Аналогично для других типов --- */
static void fill_long_array(long *arr, size_t n, int bigNumbers) {
	size_t i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = bigNumbers ? (long)(my_rand() * 100000L - 50000000L) : (long)(my_rand() % 100 - 50);
    }
}

static void fill_float_array(float *arr, size_t n, int bigNumbers) {
	size_t i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = bigNumbers ? ((float)my_rand() / UINT32_MAX * 1e6f - 5e5f) : ((float)my_rand() / UINT32_MAX * 100.0f - 50.0f);
    }
}

static void fill_double_array(double *arr, size_t n, int bigNumbers) {
	size_t i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = bigNumbers ? ((double)my_rand() / UINT32_MAX * 1e12 - 5e11) : ((double)my_rand() / UINT32_MAX * 100.0 - 50.0);
    }
}

static void fill_longdouble_array(long double *arr, size_t n, int bigNumbers) {
	size_t i = 0;
    for (i = 0; i < n; i++) {
        arr[i] = bigNumbers ? ((long double)my_rand() / UINT32_MAX * 1e18L - 5e17L) : ((long double)my_rand() / UINT32_MAX * 100.0L - 50.0L);
    }
}

/*
 *
 * <сводка>
 *   is_sorted_*
 * </сводка>
 *
 * <описание>
 *   Проверяет, отсортирован ли массив (по возрастанию/убыванию).
 * </описание>
 *
 */
static int is_sorted_int(int *arr, size_t n, int ascending) {
    if (n <= 1) return 1;

    if (ascending) {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] > arr[i]) return 0;
        }
    } else {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] < arr[i]) return 0;
        }
    }
    return 1;
}

/* --- Аналогично для других типов --- */
static int is_sorted_long(long *arr, size_t n, int ascending) {
    if (n <= 1) return 1;

    if (ascending) {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] > arr[i]) return 0;
        }
    } else {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] < arr[i]) return 0;
        }
    }
    return 1;
}

static int is_sorted_float(float *arr, size_t n, int ascending) {
    if (n <= 1) return 1;

    if (ascending) {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] > arr[i]) return 0;
        }
    } else {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] < arr[i]) return 0;
        }
    }
    return 1;
}

static int is_sorted_double(double *arr, size_t n, int ascending) {
    if (n <= 1) return 1;

    if (ascending) {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] > arr[i]) return 0;
        }
    } else {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] < arr[i]) return 0;
        }
    }
    return 1;
}

static int is_sorted_longdouble(long double *arr, size_t n, int ascending) {
    if (n <= 1) return 1;

    if (ascending) {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] > arr[i]) return 0;
        }
    } else {
		size_t i = 1;
        for (i = 1; i < n; i++) {
            if (arr[i-1] < arr[i]) return 0;
        }
    }
    return 1;
}

/*
 *
 * <сводка>
 *   cmp_*_qsort
 * </сводка>
 *
 * <описание>
 *   Сравнительные функции для qsort.
 * </описание>
 *
 */
int __cdecl  cmp_int_qsort(const void *a, const void *b) { return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b); }
int __cdecl  cmp_long_qsort(const void *a, const void *b) { return (*(long*)a > *(long*)b) - (*(long*)a < *(long*)b); }
int __cdecl  cmp_float_qsort(const void *a, const void *b) { return (*(float*)a > *(float*)b) - (*(float*)a < *(float*)b); }
int __cdecl  cmp_double_qsort(const void *a, const void *b) { return (*(double*)a > *(double*)b) - (*(double*)a < *(double*)b); }
int __cdecl  cmp_longdouble_qsort(const void *a, const void *b) { return (*(long double*)a > *(long double*)b) - (*(long double*)a < *(long double*)b); }

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
	fflush(stdout);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* ========== ТЕСТЫ производительности и корректности ========== */
    {
        /* Список размеров */
        size_t sizes[] = { 1000, 10000, 100000, 500000, 1000000 };
        size_t sizes_count = sizeof(sizes) / sizeof(sizes[0]);
		size_t si = 0;

        /* Для единообразия флаг: 1 = сортировать по возрастанию */
        int ascending = 1;

        /* Временные переменные */
        clock_t t0, t1;
        double time_bitonic, time_qsort;
        int ok;

        printf("\n=== Performance tests (Bitonic vs qsort) ===\n");

        /* ---------- INT ---------- */
        printf("\n-- Type: int --\n");
        for (si = 0; si < sizes_count; ++si) {
            size_t n = sizes[si];

            /* Выделяем массивы через pIMem */
            int *arr = (int*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(int));
            int *arr_copy = (int*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(int));
            if (arr == 0 || arr_copy == 0) {
                printf("int: Alloc failed for n=%Iu\n", n);
                if (arr) pIMem->pVTbl->Free(pIMem, arr);
                if (arr_copy) pIMem->pVTbl->Free(pIMem, arr_copy);
                continue;
            }

            /* Заполняем (для больших n ставим bigNumbers=1 для разнообразия) */
            fill_int_array(arr, n, n >= 100000 ? 1 : 0);
            copy_array(arr_copy, arr, sizeof(int), n);

            /* Bitonic */
            t0 = clock();
            pIEcoLab1->pVTbl->CEcoLab1_bitonicSort_int(pIEcoLab1, arr, n, ascending);
            t1 = clock();
            time_bitonic = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            /* Проверка корректности (время проверки не учитываем) */
            ok = is_sorted_int(arr, n, ascending);

            /* qsort */
            t0 = clock();
            qsort(arr_copy, n, sizeof(int), cmp_int_qsort);
            t1 = clock();
            time_qsort = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            /* Вывод результатов */
            printf("n=%8Iu : bitonic=%.3f s, qsort=%.3f s, bitonic_ok=%s\n",
                n, time_bitonic, time_qsort, ok ? "YES" : "NO");

            /* Освобождение */
            pIMem->pVTbl->Free(pIMem, arr);
            pIMem->pVTbl->Free(pIMem, arr_copy);
        }

        /* ---------- LONG ---------- */
        printf("\n-- Type: long --\n");
        for (si = 0; si < sizes_count; ++si) {
            size_t n = sizes[si];
            long *arr = (long*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long));
            long *arr_copy = (long*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long));
            if (arr == 0 || arr_copy == 0) {
                printf("long: Alloc failed for n=%Iu\n", n);
                if (arr) pIMem->pVTbl->Free(pIMem, arr);
                if (arr_copy) pIMem->pVTbl->Free(pIMem, arr_copy);
                continue;
            }

            fill_long_array(arr, n, n >= 100000 ? 1 : 0);
            copy_array(arr_copy, arr, sizeof(long), n);

            t0 = clock();
            pIEcoLab1->pVTbl->CEcoLab1_bitonicSort_long(pIEcoLab1, arr, n, ascending);
            t1 = clock();
            time_bitonic = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
            ok = is_sorted_long(arr, n, ascending);

            t0 = clock();
            qsort(arr_copy, n, sizeof(long), cmp_long_qsort);
            t1 = clock();
            time_qsort = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            printf("n=%8Iu : bitonic=%.3f s, qsort=%.3f s, bitonic_ok=%s\n",
                n, time_bitonic, time_qsort, ok ? "YES" : "NO");

            pIMem->pVTbl->Free(pIMem, arr);
            pIMem->pVTbl->Free(pIMem, arr_copy);
        }

        /* ---------- FLOAT ---------- */
        printf("\n-- Type: float --\n");
        for (si = 0; si < sizes_count; ++si) {
            size_t n = sizes[si];
            float *arr = (float*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(float));
            float *arr_copy = (float*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(float));
            if (arr == 0 || arr_copy == 0) {
                printf("float: Alloc failed for n=%Iu\n", n);
                if (arr) pIMem->pVTbl->Free(pIMem, arr);
                if (arr_copy) pIMem->pVTbl->Free(pIMem, arr_copy);
                continue;
            }

            fill_float_array(arr, n, n >= 100000 ? 1 : 0);
            copy_array(arr_copy, arr, sizeof(float), n);

            t0 = clock();
            pIEcoLab1->pVTbl->CEcoLab1_bitonicSort_float(pIEcoLab1, arr, n, ascending);
            t1 = clock();
            time_bitonic = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
            ok = is_sorted_float(arr, n, ascending);

            t0 = clock();
            qsort(arr_copy, n, sizeof(float), cmp_float_qsort);
            t1 = clock();
            time_qsort = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            printf("n=%8Iu : bitonic=%.3f s, qsort=%.3f s, bitonic_ok=%s\n",
                n, time_bitonic, time_qsort, ok ? "YES" : "NO");

            pIMem->pVTbl->Free(pIMem, arr);
            pIMem->pVTbl->Free(pIMem, arr_copy);
        }

        /* ---------- DOUBLE ---------- */
        printf("\n-- Type: double --\n");
        for (si = 0; si < sizes_count; ++si) {
            size_t n = sizes[si];
            double *arr = (double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(double));
            double *arr_copy = (double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(double));
            if (arr == 0 || arr_copy == 0) {
                printf("double: Alloc failed for n=%Iu\n", n);
                if (arr) pIMem->pVTbl->Free(pIMem, arr);
                if (arr_copy) pIMem->pVTbl->Free(pIMem, arr_copy);
                continue;
            }

            fill_double_array(arr, n, n >= 100000 ? 1 : 0);
            copy_array(arr_copy, arr, sizeof(double), n);

            t0 = clock();
            pIEcoLab1->pVTbl->CEcoLab1_bitonicSort_double(pIEcoLab1, arr, n, ascending);
            t1 = clock();
            time_bitonic = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
            ok = is_sorted_double(arr, n, ascending);

            t0 = clock();
            qsort(arr_copy, n, sizeof(double), cmp_double_qsort);
            t1 = clock();
            time_qsort = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            printf("n=%8Iu : bitonic=%.3f s, qsort=%.3f s, bitonic_ok=%s\n",
                n, time_bitonic, time_qsort, ok ? "YES" : "NO");

            pIMem->pVTbl->Free(pIMem, arr);
            pIMem->pVTbl->Free(pIMem, arr_copy);
        }

		/* ---------- LONG DOUBLE ---------- */
		printf("\n-- Type: long double --\n");
		for (si = 0; si < sizes_count; ++si) {
            size_t n = sizes[si];
            long double *arr = (long double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long double));
            long double *arr_copy = (long double*)pIMem->pVTbl->Alloc(pIMem, n * sizeof(long double));
            if (arr == 0 || arr_copy == 0) {
                printf("long double: Alloc failed for n=%Iu\n", n);
                if (arr) pIMem->pVTbl->Free(pIMem, arr);
                if (arr_copy) pIMem->pVTbl->Free(pIMem, arr_copy);
                continue;
            }

            fill_longdouble_array(arr, n, n >= 100000 ? 1 : 0);
            copy_array(arr_copy, arr, sizeof(long double), n);

            t0 = clock();
            pIEcoLab1->pVTbl->CEcoLab1_bitonicSort_longdouble(pIEcoLab1, arr, n, ascending);
            t1 = clock();
            time_bitonic = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
            ok = is_sorted_longdouble(arr, n, ascending);

            t0 = clock();
            qsort(arr_copy, n, sizeof(long double), cmp_longdouble_qsort);
            t1 = clock();
            time_qsort = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;

            printf("n=%8Iu : bitonic=%.3f s, qsort=%.3f s, bitonic_ok=%s\n",
                n, time_bitonic, time_qsort, ok ? "YES" : "NO");

            pIMem->pVTbl->Free(pIMem, arr);
            pIMem->pVTbl->Free(pIMem, arr_copy);
        }

        printf("\n=== Tests finished ===\n");

		result = 0;
    }


Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

