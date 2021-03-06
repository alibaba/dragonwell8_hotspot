/*
 * Copyright (c) 2020 Alibaba Group Holding Limited. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation. Alibaba designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "precompiled.hpp"
#include "prims/tenantenv.h"
#include "runtime/globals.hpp"

/**
 * Be careful: any change to the following constant defintions, you MUST
 * synch up them with ones defined in com.alibaba.tenant.TenantGlobals
 */

#define TENANT_FLAG_MULTI_TENANT_ENABLED             (0x1)    // bit 0 to indicate if the tenant feature is enabled.
#define TENANT_FLAG_HEAP_THROTTLING_ENABLED          (0x2)    // bit 1 to indicate if heap throttling feature is enabled.
#define TENANT_FLAG_CPU_THROTTLING_ENABLED           (0x4)    // bit 2 to indicate if cpu throttling feature is enabled.
#define TENANT_FLAG_DATA_ISOLATION_ENABLED           (0x8)    // bit 3 to indicate if data isolation(e.g static vairable isolation) feature is enabled.
#define TENANT_FLAG_CPU_ACCOUNTING_ENABLED          (0x40)    // bit 6 to indicate if cpu accounting feature is enabled.
#define TENANT_FLAG_HEAP_ISOLATION_ENABLED          (0x80)    // bit 7 to indicate if heap isolation feature is enabled.

static jint tenant_GetTenantFlags(TenantEnv *env, jclass cls);

static struct TenantNativeInterface_ tenantNativeInterface = {
  tenant_GetTenantFlags
};

struct TenantNativeInterface_* tenant_functions()
{
  return &tenantNativeInterface;
}

static jint
tenant_GetTenantFlags(TenantEnv *env, jclass cls)
{
  jint result = 0x0;

  if (MultiTenant) {
    result |= TENANT_FLAG_MULTI_TENANT_ENABLED;
  }

  if (TenantHeapThrottling) {
    result |= TENANT_FLAG_HEAP_THROTTLING_ENABLED;
  }

  if (TenantHeapIsolation) {
    result |= TENANT_FLAG_HEAP_ISOLATION_ENABLED;
  }

  if (TenantCpuThrottling) {
    result |= TENANT_FLAG_CPU_THROTTLING_ENABLED;
  }

  if (TenantCpuAccounting) {
    result |= TENANT_FLAG_CPU_ACCOUNTING_ENABLED;
  }

  if (TenantDataIsolation) {
    result |= TENANT_FLAG_DATA_ISOLATION_ENABLED;
  }

  return result;
}
