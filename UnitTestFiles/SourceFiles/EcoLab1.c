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

	result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A3F9C1D2E4B5678F9A0B12C3D4E5F678);
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

