/*******************************************************************************
*   Ledger Blue - Bitcoin Wallet
*   (c) 2016 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#ifndef BTCHIP_FS_H

#define BTCHIP_FS_H

#include "os.h"
#include "btchip_config.h"
#include "btchip_context.h"
#include "btchip_filesystem_tx.h"

enum btchip_supported_modes_e {
    BTCHIP_SUPPORTED_MODE_WALLET = 0x01,
    BTCHIP_SUPPORTED_MODE_RELAXED_WALLET = 0x02,
    BTCHIP_SUPPORTED_MODE_SERVER = 0x04,
    BTCHIP_SUPPORTED_MODE_DEVELOPER = 0x08
};

struct btchip_config_s {
    secu8 supportedModes;
    secu8 operationMode;
    unsigned char options;
    unsigned char payToAddressVersion;
    unsigned char payToScriptHashVersion;
};
typedef struct btchip_config_s btchip_config_t;

typedef struct btchip_backup_area_s {
    btchip_config_t config;
    // TODO : replace by AES key, review signature policy
    cx_des_key_t trustedinput_key;

} btchip_backup_area_t;

typedef struct btchip_storage_s {
    unsigned char storageInitialized;

    unsigned char config_valid;
    btchip_backup_area_t bkp;

} btchip_storage_t;

// the global nvram memory variable
extern WIDE btchip_storage_t N_btchip_real;

#define N_btchip (*(WIDE btchip_storage_t *)PIC(&N_btchip_real))

void btchip_set_operation_mode(unsigned char operationMode);

#endif