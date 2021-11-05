/*******************************************************************************
 *
 * Copyright (c) 2014 Bosch Software Innovations GmbH, Germany.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v20.html
 * The Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Bosch Software Innovations GmbH - Please refer to git log
 *
 *******************************************************************************/
/*
 * lwm2mclient.h
 *
 *  General functions of lwm2m test client.
 *
 *  Created on: 22.01.2015
 *  Author: Achim Kraus
 *  Copyright (c) 2015 Bosch Software Innovations GmbH, Germany. All rights reserved.
 */

#ifndef LWM2MCLIENT_H_
#define LWM2MCLIENT_H_

#include "liblwm2m.h"

#if defined WITH_MBEDTLS
#include "mbedtls/build_info.h"
#ifdef MBEDTLS_X509_CRT_PARSE_C
#include "mbedtls/x509.h"
#include "mbedtls/x509_crt.h"
#endif /* MBEDTLS_X509_CRT_PARSE_C */
#else 
#include "connection.h"
#endif /* WITH_MBEDTLS */

extern int g_reboot;

/*
 * object_device.c
 */
lwm2m_object_t * get_object_device(void);
void free_object_device(lwm2m_object_t * objectP);
uint8_t device_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);
void display_device_object(lwm2m_object_t * objectP);
/*
 * object_firmware.c
 */
lwm2m_object_t * get_object_firmware(void);
void free_object_firmware(lwm2m_object_t * objectP);
void display_firmware_object(lwm2m_object_t * objectP);
/*
 * object_location.c
 */
lwm2m_object_t * get_object_location(void);
void free_object_location(lwm2m_object_t * object);
void display_location_object(lwm2m_object_t * objectP);
/*
 * object_test.c
 */
#define TEST_OBJECT_ID 31024
lwm2m_object_t * get_test_object(void);
void free_test_object(lwm2m_object_t * object);
void display_test_object(lwm2m_object_t * objectP);
/*
 * object_server.c
 */
lwm2m_object_t * get_server_object(int serverId, const char* binding, int lifetime, bool storing);
void clean_server_object(lwm2m_object_t * object);
void display_server_object(lwm2m_object_t * objectP);
void copy_server_object(lwm2m_object_t * objectDest, lwm2m_object_t * objectSrc);

/*
 * object_connectivity_moni.c
 */
lwm2m_object_t * get_object_conn_m(void);
void free_object_conn_m(lwm2m_object_t * objectP);
uint8_t connectivity_moni_change(lwm2m_data_t * dataArray, lwm2m_object_t * objectP);

/*
 * object_connectivity_stat.c
 */
extern lwm2m_object_t * get_object_conn_s(void);
void free_object_conn_s(lwm2m_object_t * objectP);
extern void conn_s_updateTxStatistic(lwm2m_object_t * objectP, uint16_t txDataByte, bool smsBased);
extern void conn_s_updateRxStatistic(lwm2m_object_t * objectP, uint16_t rxDataByte, bool smsBased);

/*
 * object_access_control.c
 */
lwm2m_object_t* acc_ctrl_create_object(void);
void acl_ctrl_free_object(lwm2m_object_t * objectP);
bool  acc_ctrl_obj_add_inst (lwm2m_object_t* accCtrlObjP, uint16_t instId,
                 uint16_t acObjectId, uint16_t acObjInstId, uint16_t acOwner);
bool  acc_ctrl_oi_add_ac_val(lwm2m_object_t* accCtrlObjP, uint16_t instId,
                 uint16_t aclResId, uint16_t acValue);
/*
 * lwm2mclient.c
 */
void handle_value_changed(lwm2m_context_t* lwm2mH, lwm2m_uri_t* uri, const char * value, size_t valueLength);
/*
 * system_api.c
 */
void init_value_change(lwm2m_context_t * lwm2m);
void system_reboot(void);

/*
 * object_security.c
 */
lwm2m_object_t * get_security_object(int serverId,
                                     const char* serverUri,
                                     uint8_t securityMode,
                                     bool isBootstrap);
void clean_security_object(lwm2m_object_t * objectP);
char * get_server_uri(lwm2m_object_t * objectP, uint16_t secObjInstID);
void display_security_object(lwm2m_object_t * objectP);
void copy_security_object(lwm2m_object_t * objectDest, lwm2m_object_t * objectSrc);

typedef struct
{
    lwm2m_object_t * securityObjP;
    lwm2m_object_t * serverObject;
    lwm2m_context_t * ctx;
#if defined WITH_MBEDTLS
    int force_ciphersuite[2];   /* protocol/ciphersuite to use, or all      */

#if defined(MBEDTLS_SSL_DTLS_CONNECTION_ID)
    unsigned char cid[MBEDTLS_SSL_CID_IN_LEN_MAX];
    size_t cid_len;   
#endif /* MBEDTLS_SSL_DTLS_CONNECTION_ID */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    mbedtls_x509_crt * cacert;
    mbedtls_x509_crt * clicert;
    mbedtls_pk_context * pkey;
#endif /* MBEDTLS_X509_CRT_PARSE_C */

#if defined(MBEDTLS_USE_PSA_CRYPTO) && defined(MBEDTLS_X509_CRT_PARSE_C)
    psa_key_id_t key_slot;
#endif /* MBEDTLS_USE_PSA_CRYPTO && MBEDTLS_X509_CRT_PARSE_C */

#else /* WITH_MBEDTLS */
    int sock;
#ifdef WITH_TINYDTLS
    dtls_connection_t * connList;
    lwm2m_context_t * lwm2mH;
#else /* WITH_TINYDTLS */
    connection_t * connList;
#endif /* WITH_TINYDTLS */

#endif /* WITH_MBEDTLS */

#if ( defined(WITH_MBEDTLS) && defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED) ) || defined(WITH_TINYDTLS)
    uint8_t * psk_identity;
    uint16_t psk_identity_len;
    uint8_t * psk;
    uint16_t psk_len;
#endif /* WITH_MBEDTLS && MBEDTLS_KEY_EXCHANGE_PSK_ENABLED || WITH_TINYDTLS */

    int addressFamily;
} client_data_t;

#endif /* LWM2MCLIENT_H_ */
