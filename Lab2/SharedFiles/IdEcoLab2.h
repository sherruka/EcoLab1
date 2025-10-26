/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoLab2
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

#ifndef __ID_ECOLAB2_H__
#define __ID_ECOLAB2_H__

#include "IEcoBase1.h"
#include "IEcoLab2.h"

/* EcoLab2 CID = {A1B2C3D4-E5F6-47A8-90AB-CDEF12345678} */
#ifndef __CID_EcoLab2
static const UGUID CID_EcoLab2 = {0x01, 0x10, {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x47, 0xA8, 0x90, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78}};
#endif /* __CID_EcoLab2 */

/* Фабрика компонента для динамической и статической компоновки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_A1B2C3D4E5F647A890ABCDEF12345678;
#endif

#endif /* __ID_ECOLAB2_H__ */