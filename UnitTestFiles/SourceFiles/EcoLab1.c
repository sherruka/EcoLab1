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
#include "IdEcoLab2.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IEcoLab1.h"
#include "IEcoLab1Events.h"
#include "CEcoLab1Sink.h"


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
	IEcoLab2* pIEcoLab2 = 0;
	IEcoCalculatorX* pIX = 0;
	IEcoCalculatorY* pIY = 0;
	IEcoLab1* pIEcoLab1_2 = 0;

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
        printf("ERROR: Failed to register Eco.Lab1 component! Error code: %d\n", result);
        goto Release;
    }

	result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A1B2C3D4E5F647A890ABCDEF12345678);
    if (result != 0 ) { 
		printf("ERROR: Failed to register Eco.Lab2 component! Error code: %d\n", result);
		goto Release; 
	}
#endif

#ifdef ECO_DLL
	result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown*)GetIEcoComponentFactoryPtr());
    if (result != 0 ) { 
		printf("ERROR: Failed to register Eco.Lab2 component! Error code: %d\n", result);
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

	/* ======= ТЕСТ: Использование IEcoCalculator через IEcoLab1 ======= */
    {
        pIEcoLab1 = 0;
		pIX = 0;
		pIY = 0;

		printf("\n========== LAB1 TESTS ==========\n\n");

		// Получаем компонент
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		// Тестируем QueryInterface
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		/* Test 1 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: 5 + 3 = %d\n", pIX->pVTbl->Addition(pIX, 5, 3)); 
			printf("Subtraction: 10 - 4 = %d\n", pIX->pVTbl->Subtraction(pIX, 10, 4)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: 5 * 3 = %d\n", pIY->pVTbl->Multiplication(pIY, 5, 3)); 
			printf("Division: 6 / 3 = %d\n", pIY->pVTbl->Division(pIY, 6, 3)); 
			pIY->pVTbl->Release(pIY); 
		}

		/* Test 2 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: 2 + 9 = %d\n", pIX->pVTbl->Addition(pIX, 2, 9)); 
			printf("Subtraction: -1 - (-5) = %d\n", pIX->pVTbl->Subtraction(pIX, -1, -5)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: 7 * 7 = %d\n", pIY->pVTbl->Multiplication(pIY, 7, 7)); 
			printf("Division: 20 / 4 = %d\n", pIY->pVTbl->Division(pIY, 20, 4)); 
			pIY->pVTbl->Release(pIY); 
		}

		/* Test 3 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: 123 + 321 = %d\n", pIX->pVTbl->Addition(pIX, 123, 321)); 
			printf("Subtraction: 15 - 8 = %d\n", pIX->pVTbl->Subtraction(pIX, 15, 8)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: 11 * 11 = %d\n", pIY->pVTbl->Multiplication(pIY, 11, 11)); 
			printf("Division: 100 / 25 = %d\n", pIY->pVTbl->Division(pIY, 100, 25)); 
			pIY->pVTbl->Release(pIY); 
		}

		/* Test 4 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: 8 + 12 = %d\n", pIX->pVTbl->Addition(pIX, 8, 12)); 
			printf("Subtraction: 20 - 7 = %d\n", pIX->pVTbl->Subtraction(pIX, 20, 7)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: 6 * 9 = %d\n", pIY->pVTbl->Multiplication(pIY, 6, 9)); 
			printf("Division: 45 / 5 = %d\n", pIY->pVTbl->Division(pIY, 45, 5)); 
			pIY->pVTbl->Release(pIY); 
		}

		/* Test 5 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: 0 + 100 = %d\n", pIX->pVTbl->Addition(pIX, 0, 100)); 
			printf("Subtraction: 50 - 25 = %d\n", pIX->pVTbl->Subtraction(pIX, 50, 25)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: 12 * 12 = %d\n", pIY->pVTbl->Multiplication(pIY, 12, 12)); 
			printf("Division: 81 / 9 = %d\n", pIY->pVTbl->Division(pIY, 81, 9)); 
			pIY->pVTbl->Release(pIY); 
		}

		/* Test 6 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) { 
			printf("Addition: -10 + 15 = %d\n", pIX->pVTbl->Addition(pIX, -10, 15)); 
			printf("Subtraction: 7 - 14 = %d\n", pIX->pVTbl->Subtraction(pIX, 7, 14)); 
			pIX->pVTbl->Release(pIX); 
		}
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) { 
			printf("Multiplication: -3 * 6 = %d\n", pIY->pVTbl->Multiplication(pIY, -3, 6)); 
			printf("Division: 14 / 2 = %d\n", pIY->pVTbl->Division(pIY, 14, 2)); 
			pIY->pVTbl->Release(pIY); 
		}

		// Демонстрируем свойства интерфейсов
		printf("\nInterface properties:\n");

		/* Prop 1 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0; pIEcoLab1_2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) {
			result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void**)&pIY);
			if (result == 0 && pIY) {
				result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void**)&pIEcoLab1_2);
				if (result == 0 && pIEcoLab1_2) {
					printf("Prop1: IEcoLab1 -> IX -> IY -> IEcoLab1 OK\n");
					printf("Example: 2 + 3 = %d\n", pIX->pVTbl->Addition(pIX, 2, 3));
					pIEcoLab1_2->pVTbl->Release(pIEcoLab1_2);
				}
				pIY->pVTbl->Release(pIY);
			}
			pIX->pVTbl->Release(pIX);
		}

		/* Prop 2 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0; pIEcoLab1_2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIY);
		if (result == 0 && pIY) {
			result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**)&pIX);
			if (result == 0 && pIX) {
				result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void**)&pIEcoLab1_2);
				if (result == 0 && pIEcoLab1_2) {
					printf("Prop2: IEcoLab1 -> IY -> IX -> IEcoLab1 OK\n");
					printf("Example: 10 - 4 = %d\n", pIX->pVTbl->Subtraction(pIX, 10, 4));
					pIEcoLab1_2->pVTbl->Release(pIEcoLab1_2);
				}
				pIX->pVTbl->Release(pIX);
			}
			pIY->pVTbl->Release(pIY);
		}

		/* Prop 3 */
		pIEcoLab1 = 0; pIX = 0; pIY = 0; pIEcoLab1_2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pIEcoLab1);
		result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIX);
		if (result == 0 && pIX) {
			result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void**)&pIY);
			if (result == 0 && pIY) {
				result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**)&pIX);
				if (result == 0 && pIX) {
					printf("Prop5: IX -> IY -> IX OK\n");
					printf("Example: 9 - 4 = %d\n", pIX->pVTbl->Subtraction(pIX, 9, 4));
					pIX->pVTbl->Release(pIX);
				}
				pIY->pVTbl->Release(pIY);
			}
			pIX->pVTbl->Release(pIX);
		}

		printf("\n========== END LAB1 TESTS ==========\n\n\n\n");
    }


	/* ======= ТЕСТ: Использование IEcoLab2 и агрегированного EcoLab1 ======= */
    {
		IEcoCalculatorX* pIX_Lab2 = 0;
		IEcoCalculatorY* pIY_Lab2 = 0;
		IEcoLab1* pIEcoLab1_FromLab2 = 0;
		pIEcoLab2 = 0;

		printf("\n========== LAB2 TESTS ==========\n\n");

		/* ======= TEST 1: Базовые операции Lab2 (Bitonic Sort для int) ======= */
		printf("--- Test 1: Lab2 bitonicSort_int ---\n");
		pIEcoLab2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			int arr1[5] = { 50, 20, 80, 10, 30 };
			size_t i;
			printf("Original: ");
			for (i = 0; i < 5; i++) printf("%d ", arr1[i]);
			printf("\n");
			
			result = pIEcoLab2->pVTbl->CEcoLab2_bitonicSort_int(pIEcoLab2, arr1, 5, 1); // ascending
			printf("Sorted: ");
			for (i = 0; i < 5; i++) printf("%d ", arr1[i]);
			printf("\n");
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}


		/* ======= TEST 2: Lab2 Calculator X operations via QueryInterface ======= */
		printf("\n--- Test 2: Lab2 as IEcoCalculatorX (from IEcoLab2) ---\n");
		pIEcoLab2 = 0;
		pIX_Lab2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**)&pIX_Lab2);
			if (result == 0 && pIX_Lab2) {
				printf("Addition: 25 + 15 = %d\n", pIX_Lab2->pVTbl->Addition(pIX_Lab2, 25, 15));
				printf("Subtraction: 50 - 20 = %d\n", pIX_Lab2->pVTbl->Subtraction(pIX_Lab2, 50, 20));
				pIX_Lab2->pVTbl->Release(pIX_Lab2);
			}
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}

		/* ======= TEST 3: Lab2 Calculator Y operations via QueryInterface ======= */
		printf("\n--- Test 3: Lab2 as IEcoCalculatorY (from IEcoLab2) ---\n");
		pIEcoLab2 = 0;
		pIY_Lab2 = 0;
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorY, (void**)&pIY_Lab2);
			if (result == 0 && pIY_Lab2) {
				printf("Multiplication: 12 * 8 = %d\n", pIY_Lab2->pVTbl->Multiplication(pIY_Lab2, 12, 8));
				printf("Division: 100 / 4 = %d\n", pIY_Lab2->pVTbl->Division(pIY_Lab2, 100, 4));
				pIY_Lab2->pVTbl->Release(pIY_Lab2);
			}
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}

		/* ======= TEST 4: QueryInterface chain X -> Y -> Lab2 -> Lab1 (aggregation) ======= */
		printf("\n--- Test 4: QueryInterface chain - ILab2 -> IX -> IY -> ILab1 ---\n");
		pIEcoLab2 = 0;
		pIX_Lab2 = 0;
		pIY_Lab2 = 0;
		pIEcoLab1_FromLab2 = 0;
		
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			// Get IX from Lab2
			result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**)&pIX_Lab2);
			if (result == 0 && pIX_Lab2) {
				// Get IY from IX
				result = pIX_Lab2->pVTbl->QueryInterface(pIX_Lab2, &IID_IEcoCalculatorY, (void**)&pIY_Lab2);
				if (result == 0 && pIY_Lab2) {
					// Get ILab2 from IY
					result = pIY_Lab2->pVTbl->QueryInterface(pIY_Lab2, &IID_IEcoLab1, (void**)&pIEcoLab1_FromLab2);
					if (result == 0 && pIEcoLab1_FromLab2) {
						// Get ILab1 from ILab2
						if (result == 0 && pIEcoLab1_FromLab2) {
							int arr1[3] = { 4, 3, 7 };
							int i;
							printf("Step 1 - IX Addition: 10 + 5 = %d\n", pIX_Lab2->pVTbl->Addition(pIX_Lab2, 10, 5));
							printf("Step 2 - IY Multiplication: 10 * 5 = %d\n", pIY_Lab2->pVTbl->Multiplication(pIY_Lab2, 10, 5));
							printf("Step 3 - Lab1: sort [4, 3, 7] = ", pIEcoLab1_FromLab2->pVTbl->CEcoLab1_bitonicSort_int(pIEcoLab1_FromLab2, arr1, 3, 1));
							for (i = 0; i < 3; i++) printf("%d ", arr1[i]);
							printf("\nSuccessfully traversed: ILab2 -> IX -> IY -> ILab1\n");
						}
						pIEcoLab1_FromLab2->pVTbl->Release(pIEcoLab1_FromLab2);	
					}
					pIY_Lab2->pVTbl->Release(pIY_Lab2);
				}
				pIX_Lab2->pVTbl->Release(pIX_Lab2);
			}
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}

		/* ======= TEST 5: Access aggregated Lab1 from Lab2 ======= */
		printf("\n--- Test 5: Access aggregated EcoLab1 from Lab2 via QueryInterface ---\n");
		pIEcoLab2 = 0;
		pIEcoLab1_FromLab2 = 0;
		
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			// Try to get Lab1 interface from Lab2 (should work via aggregation)
			result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoLab1, (void**)&pIEcoLab1_FromLab2);
			if (result == 0 && pIEcoLab1_FromLab2) {
				int arr_test[3] = { 30, 10, 20 };
				size_t i;
				printf("Successfully retrieved aggregated IEcoLab1 from Lab2!\n");
				printf("Lab1 array before sort: ");
				for (i = 0; i < 3; i++) printf("%d ", arr_test[i]);
				printf("\n");
				
				pIEcoLab1_FromLab2->pVTbl->CEcoLab1_bitonicSort_int(pIEcoLab1_FromLab2, arr_test, 3, 1);
				printf("Lab1 array after sort: ");
				for (i = 0; i < 3; i++) printf("%d ", arr_test[i]);
				printf("\n");
				
				pIEcoLab1_FromLab2->pVTbl->Release(pIEcoLab1_FromLab2);
			} else {
				printf("Note: Aggregated Lab1 not available or not registered\n");
			}
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}

		/* ======= TEST 6: Interface properties - cross-interface operations ======= */
		printf("\n--- Test 6: Lab2 Interface Properties (IX -> IY -> IX cycles) ---\n");
		pIEcoLab2 = 0;
		pIX_Lab2 = 0;
		pIY_Lab2 = 0;
		
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**)&pIEcoLab2);
		if (result == 0 && pIEcoLab2) {
			result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**)&pIX_Lab2);
			if (result == 0 && pIX_Lab2) {
				printf("Addition: 7 + 3 = %d\n", pIX_Lab2->pVTbl->Addition(pIX_Lab2, 7, 3));
				
				result = pIX_Lab2->pVTbl->QueryInterface(pIX_Lab2, &IID_IEcoCalculatorY, (void**)&pIY_Lab2);
				if (result == 0 && pIY_Lab2) {
					printf("Multiplication: 7 * 3 = %d\n", pIY_Lab2->pVTbl->Multiplication(pIY_Lab2, 7, 3));
					
					// Cycle back
					result = pIY_Lab2->pVTbl->QueryInterface(pIY_Lab2, &IID_IEcoCalculatorX, (void**)&pIX_Lab2);
					if (result == 0 && pIX_Lab2) {
						printf("Subtraction (cycled back): 7 - 3 = %d\n", pIX_Lab2->pVTbl->Subtraction(pIX_Lab2, 7, 3));
					}
					pIY_Lab2->pVTbl->Release(pIY_Lab2);
				}
				pIX_Lab2->pVTbl->Release(pIX_Lab2);
			}
			pIEcoLab2->pVTbl->Release(pIEcoLab2);
		}
		printf("\n========== END LAB2 TESTS ==========\n\n\n\n");
	}


	/* ======= ТЕСТ ОБРАБОТКИ СОБЫТИЙ: Демонстрация Many-to-Many (несколько получателей - несколько компонентов) ======= */
    {
		IEcoLab1* pComp1 = 0;
		IEcoLab1* pComp2 = 0;
        IEcoLab1* pComp3 = 0;
		IEcoLab1* pComp4 = 0;
        IEcoLab1* pComp5 = 0;
        IEcoLab1Events* pSink1 = 0;
        IEcoLab1Events* pSink2 = 0;
        IEcoLab1Events* pSink3 = 0;
        IEcoLab1Events* pSink4 = 0;
        IEcoLab1Events* pSink5 = 0;
        IEcoLab1Events* pSink6 = 0;
		IEcoLab1Events* pSinkShared = 0;
		printf("\n========== LAB3 TESTS ==========\n\n");
        printf("Demonstrating full event-driven architecture:\n");
        printf("- (1-to-many)\n");
        printf("- (many-to-1)\n");
        printf("- (many-to-many)\n\n");
     
        /* ===== ТЕСТ 1: Один компонент — два приёмника (1-ко-многим) ===== */
        printf("--- TEST 1: One component with two event receivers (1-to-many) ---\n");
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pComp1);
        if (result == 0 && pComp1) {
			/* Создаём и подключаем первый sink */
			if (createCEcoLab1Sink(pIMem, &pSink1) == 0) {
				CEcoLab1Sink* pS1 = (CEcoLab1Sink*)pSink1;
				pS1->Advise(pS1, pComp1);
								
				/* Создаём и подключаем второй sink */
				if (createCEcoLab1Sink(pIMem, &pSink2) == 0) {
					CEcoLab1Sink* pS2 = (CEcoLab1Sink*)pSink2;
					pS2->Advise(pS2, pComp1);
					/* Выполняем сортировку - оба sink'а получают события */
					{
						int arr[4] = { 40, 10, 30, 20 };
						int i;
						printf("\nSorting array [40, 10, 30, 20]:\n");
						printf("Both receivers (Sink 1 and Sink 2) will receive events below:\n\n");
						pComp1->pVTbl->CEcoLab1_bitonicSort_int(pComp1, arr, 4, 1);
						printf("\nResult: ");
						for (i = 0; i < 4; i++) printf("%d ", arr[i]);
						printf("\n");
					}
					/* Очистка */
					pS2->Unadvise(pS2, pComp1);
					pSink2->pVTbl->Release(pSink2);
				}
                                        
				pS1->Unadvise(pS1, pComp1);
				pSink1->pVTbl->Release(pSink1);
			}
			pComp1->pVTbl->Release(pComp1);
        }
        /* ===== ТЕСТ 2: Многие-к-1 (два компонента, один приёмник) ===== */
		printf("\n--- TEST 2: One receiver listens to two components (many-to-1) ---\n");
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pComp2);
        if (result == 0 && pComp2) {
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pComp3);
            if (result == 0 && pComp3) {
                /* Создаём общий sink */
                if (createCEcoLab1Sink(pIMem, &pSinkShared) == 0) {
                    CEcoLab1Sink* pSShared = (CEcoLab1Sink*)pSinkShared;
                    /* Подключаем один и тот же sink к обоим компонентам */
                    pSShared->Advise(pSShared, pComp2);
                    pSShared->Advise(pSShared, pComp3);
                    /* Сортировка на компоненте 2 */
                    {
                        int arr[4] = { 50, 20, 40, 60 };
                        int i;
                        printf("\nComponent 2: sorting [50, 20, 40, 60]:\n");
                        pComp2->pVTbl->CEcoLab1_bitonicSort_int(pComp2, arr, 4, 1);
                        printf("Result: ");
                        for (i = 0; i < 4; i++) printf("%d ", arr[i]);
                        printf("\n");
                    }
                    /* Сортировка на компоненте 3 */
                    {
                        int arr[4] = { 80, 10, 60, 1 };
                        int i;
                        printf("\nComponent 3: sorting [80, 10, 60, 1]:\n");
                        pComp3->pVTbl->CEcoLab1_bitonicSort_int(pComp3, arr, 4, 1);
                        printf("Result: ");
                        for (i = 0; i < 4; i++) printf("%d ", arr[i]);
                        printf("\n");
                    }
                    /* Очистка */
                    pSShared->Unadvise(pSShared, pComp2);
                    pSShared->Unadvise(pSShared, pComp3);
                    pSinkShared->pVTbl->Release(pSinkShared);
                }
                pComp3->pVTbl->Release(pComp3);
            }
            pComp2->pVTbl->Release(pComp2);
        }
        /* ===== ТЕСТ 3: Настоящий многие-ко-многим (2 компонента, 4 приёмника, разные подключения) ===== */
		printf("\n--- TEST 3: Real many-to-many (2 components, 4 receivers with different connections) ---\n");
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pComp4);
        if (result == 0 && pComp4) {
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**)&pComp5);
            if (result == 0 && pComp5) {
                /* Создаём 4 sink'а */
                if ((createCEcoLab1Sink(pIMem, &pSink3) == 0) &&
                    (createCEcoLab1Sink(pIMem, &pSink4) == 0) &&
                    (createCEcoLab1Sink(pIMem, &pSink5) == 0) &&
                    (createCEcoLab1Sink(pIMem, &pSink6) == 0)) {
					CEcoLab1Sink* pS3 = (CEcoLab1Sink*)pSink3;
					CEcoLab1Sink* pS4 = (CEcoLab1Sink*)pSink4;
					CEcoLab1Sink* pS5 = (CEcoLab1Sink*)pSink5;
					CEcoLab1Sink* pS6 = (CEcoLab1Sink*)pSink6;
                    /* Подключаем Sink3 и Sink4 к Component4 */
                    pS3->Advise((CEcoLab1Sink*)pSink3, pComp4);
                    pS4->Advise((CEcoLab1Sink*)pSink4, pComp4);
                    /* Подключаем Sink5 и Sink6 к Component5 */
                    pS5->Advise((CEcoLab1Sink*)pSink5, pComp5);
                    pS6->Advise((CEcoLab1Sink*)pSink6, pComp5);
                    /* Сортировка на Component4 - Sink3 и Sink4 получают события */
                    {
                        int arr[4] = { 70, 30, 90, 20 };
                        int i;
                        printf("\nComponent 4: sorting [70, 30, 90, 20]:\n");
                        printf("(Monitoring Sink 3 and Sink 4)\n");
                        pComp4->pVTbl->CEcoLab1_bitonicSort_int(pComp4, arr, 4, 1);
                        printf("Result: ");
                        for (i = 0; i < 4; i++) printf("%d ", arr[i]);
                        printf("\n");
                    }
                    /* Сортировка на Component5 - Sink5 и Sink6 получают события */
                    {
                        int arr[4] = { 100, 5, 55, 35 };
                        int i;
                        printf("\nComponent 5: sorting [100, 5, 55, 35]:\n");
                        printf("(Monitoring Sink 5 and Sink 6)\n");
                        pComp5->pVTbl->CEcoLab1_bitonicSort_int(pComp5, arr, 4, 1);
                        printf("Result: ");
                        for (i = 0; i < 4; i++) printf("%d ", arr[i]);
                        printf("\n");
                    }
                    /* Очистка */
                    pS3->Unadvise((CEcoLab1Sink*)pSink3, pComp4);
                    pS4->Unadvise((CEcoLab1Sink*)pSink4, pComp4);
                    pS5->Unadvise((CEcoLab1Sink*)pSink5, pComp5);
                    pS6->Unadvise((CEcoLab1Sink*)pSink6, pComp5);
                    pSink3->pVTbl->Release(pSink3);
                    pSink4->pVTbl->Release(pSink4);
                    pSink5->pVTbl->Release(pSink5);
                    pSink6->pVTbl->Release(pSink6);
                }
                pComp5->pVTbl->Release(pComp5);
            }
            pComp4->pVTbl->Release(pComp4);
        }
        printf("\n========== END OF MANY-TO-MANY TESTS ==========\n");
        printf("Successfully demonstrated event-driven architecture with:\n");
        printf("- 1-to-many: one component sending events to multiple receivers\n");
        printf("- Many-to-1: multiple components sending events to one receiver\n");
        printf("- Many-to-many: multiple components and multiple receivers with independent connections\n\n");
        printf("\n========== END LAB3 TESTS ==========\n\n");
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

	if (pIEcoLab1_2) { 
		pIEcoLab1_2->pVTbl->Release(pIEcoLab1_2);
	}

	if (pIX) { 
		pIX->pVTbl->Release(pIX);
	}

    if (pIY) { 
		pIY->pVTbl->Release(pIY);
	}

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}


