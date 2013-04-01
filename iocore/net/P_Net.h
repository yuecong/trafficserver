/** @file

  A brief file description

  @section license License

  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

/****************************************************************************

  Net Subsystem


**************************************************************************/
#ifndef __P_NET_H__
#define __P_NET_H__

// Net Stats

enum Net_Stats
{
  net_handler_run_stat,
  net_read_bytes_stat,
  net_write_bytes_stat,
  net_connections_currently_open_stat,
  net_accepts_currently_open_stat,
  net_calls_to_readfromnet_stat,
  net_calls_to_readfromnet_afterpoll_stat,
  net_calls_to_read_stat,
  net_calls_to_read_nodata_stat,
  net_calls_to_writetonet_stat,
  net_calls_to_writetonet_afterpoll_stat,
  net_calls_to_write_stat,
  net_calls_to_write_nodata_stat,
  socks_connections_successful_stat,
  socks_connections_unsuccessful_stat,
  socks_connections_currently_open_stat,
  inactivity_cop_lock_acquire_failure_stat,
  Net_Stat_Count
};

struct RecRawStatBlock;
extern RecRawStatBlock *net_rsb;
#define SSL_HANDSHAKE_WANT_READ   6
#define SSL_HANDSHAKE_WANT_WRITE  7
#define SSL_HANDSHAKE_WANT_ACCEPT 8
#define SSL_HANDSHAKE_WANT_CONNECT 9

#define NET_DEBUG_COUNT_DYN_STAT(_x, _y) \
RecIncrRawStatCount(net_rsb, mutex->thread_holding, (int)_x, _y)

#define NET_INCREMENT_DYN_STAT(_x)  \
RecIncrRawStatSum(net_rsb, mutex->thread_holding, (int)_x, 1)

#define NET_DECREMENT_DYN_STAT(_x) \
RecIncrRawStatSum(net_rsb, mutex->thread_holding, (int)_x, -1)

#define NET_SUM_DYN_STAT(_x, _r) \
RecIncrRawStatSum(net_rsb, mutex->thread_holding, (int)_x, _r)

#define NET_READ_DYN_SUM(_x, _sum)  RecGetRawStatSum(net_rsb, (int)_x, &_sum)

#define NET_READ_DYN_STAT(_x, _count, _sum) do {\
RecGetRawStatSum(net_rsb, (int)_x, &_sum);          \
RecGetRawStatCount(net_rsb, (int)_x, &_count);         \
} while (0)

#define NET_CLEAR_DYN_STAT(x) \
do { \
	RecSetRawStatSum(net_rsb, x, 0); \
	RecSetRawStatCount(net_rsb, x, 0); \
} while (0);

// For global access
#define NET_SUM_GLOBAL_DYN_STAT(_x, _r) RecIncrGlobalRawStatSum(net_rsb, (_x), (_r))
#define NET_READ_GLOBAL_DYN_SUM(_x, _sum) RecGetGlobalRawStatSum(net_rsb, _x, &_sum)

#include "libts.h"
#include "P_EventSystem.h"
#include "I_Net.h"
#include "P_NetVConnection.h"
#include "P_UnixNet.h"
#include "P_UnixNetProcessor.h"
#include "P_NetAccept.h"
#include "P_UnixNetVConnection.h"
#include "P_UnixPollDescriptor.h"
#include "P_Socks.h"
#include "P_CompletionUtil.h"
#include "P_NetVCTest.h"
#include "P_LibBulkIO.h"

#include "P_SSLNetVConnection.h"
#include "P_SSLNetProcessor.h"
#include "P_SSLNetAccept.h"
#include "P_SSLCertLookup.h"

#undef  NET_SYSTEM_MODULE_VERSION
#define NET_SYSTEM_MODULE_VERSION makeModuleVersion(                    \
                                       NET_SYSTEM_MODULE_MAJOR_VERSION, \
                                       NET_SYSTEM_MODULE_MINOR_VERSION, \
                                       PRIVATE_MODULE_HEADER)

// For very verbose iocore debugging.
#ifndef DEBUG
#define NetDebug if (0) dummy_debug
#else
#define NetDebug Debug
#endif


#endif
