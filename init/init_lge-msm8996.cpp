/*
 * Copyright (C) 2021 Project Lighthouse
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <cstdio>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/_system_properties.h>

#include "vendor_init.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

/* From Magisk@jni/magiskhide/hide_utils.c */
static const char *snet_prop_key[] = {
    "ro.boot.vbmeta.device_state",
    "ro.boot.verifiedbootstate",
    "ro.boot.flash.locked",
    "ro.boot.selinux",
    "ro.boot.veritymode",
    "ro.boot.warranty_bit",
    "ro.warranty_bit",
    "ro.debuggable",
    "ro.secure",
    "ro.build.type",
    "ro.build.tags",
    "ro.build.selinux",
    NULL
};

static const char *snet_prop_value[] = {
    "locked",
    "green",
    "1",
    "enforcing",
    "enforcing",
    "0",
    "0",
    "0",
    "1",
    "user",
    "release-keys",
    "1",
    NULL
};

static void workaround_snet_properties() {

    // Hide all sensitive props
    for (int i = 0; snet_prop_key[i]; ++i) {
        property_override(snet_prop_key[i], snet_prop_value[i]);
    }
}

static void set_build_fingerprint(const char *fingerprint){
    property_override("ro.vendor.build.fingerprint", fingerprint);
    property_override("ro.bootimage.build.fingerprint", fingerprint);
    property_override("ro.system.build.fingerprint", fingerprint);
    property_override("ro.build.fingerprint", fingerprint);
    property_override("ro.odm.build.fingerprint", fingerprint);
    property_override("ro.product.build.fingerprint", fingerprint);
    property_override("ro.system_ext.build.fingerprint", fingerprint);
}

static void set_build_description(const char *description){
    property_override("ro.build.description", description);
}

void vendor_load_properties()
{
    workaround_snet_properties();
    set_build_fingerprint("google/redfin/redfin:11/RQ3A.210905.001/7511028:user/release-keys");
    set_build_description("redfin-user 11 RQ3A.210905.001 7511028 release-keys");
}
