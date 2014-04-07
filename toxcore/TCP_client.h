/*
* TCP_client.h -- Implementation of the TCP relay client part of Tox.
*
*  Copyright (C) 2014 Tox project All Rights Reserved.
*
*  This file is part of Tox.
*
*  Tox is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  Tox is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with Tox.  If not, see <http://www.gnu.org/licenses/>.
*
*/


#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "net_crypto.h"
#include "TCP_server.h"

#define TCP_CONNECTION_TIMEOUT 10

enum {
    TCP_CLIENT_NO_STATUS,
    TCP_CLIENT_CONNECTING,
    TCP_CLIENT_UNCONFIRMED,
    TCP_CLIENT_CONFIRMED,
    TCP_CLIENT_DISCONNECTED,
};
typedef struct  {
    uint8_t status;
    sock_t  sock;
    uint8_t public_key[crypto_box_PUBLICKEYBYTES]; /* public key of the server */
    uint8_t recv_nonce[crypto_box_NONCEBYTES]; /* Nonce of received packets. */
    uint8_t sent_nonce[crypto_box_NONCEBYTES]; /* Nonce of sent packets. */
    uint8_t shared_key[crypto_box_BEFORENMBYTES];
    uint16_t next_packet_length;

    uint8_t temp_secret_key[crypto_box_SECRETKEYBYTES];

    uint8_t last_packet[2 + MAX_PACKET_SIZE];
    uint16_t last_packet_length;
    uint16_t last_packet_sent;

    uint64_t kill_at;

    uint64_t last_pinged;
    uint64_t ping_id;
} TCP_Client_Connection;

/* Create new TCP connection to ip_port/public_key
 */
TCP_Client_Connection *new_TCP_connection(IP_Port ip_port, uint8_t *public_key, uint8_t *self_public_key,
        uint8_t *self_secret_key);

/* Run the TCP connection
 */
void do_TCP_connection(TCP_Client_Connection *TCP_connection);

/* Kill the TCP connection
 */
void kill_TCP_connection(TCP_Client_Connection *TCP_connection);

int get_TCP_connection_status(TCP_Client_Connection *TCP_connection);

int read_TCP_connection(TCP_Client_Connection *TCP_connection, uint8_t *data);


#endif
