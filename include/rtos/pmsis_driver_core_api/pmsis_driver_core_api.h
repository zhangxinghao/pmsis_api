/*
 * Copyright (C) 2018 ETH Zurich, University of Bologna and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PMSIS_DRIVER_CORE_API_H__
#define __PMSIS_DRIVER_CORE_API_H__


// Open a device using its name if available
// if no name is passed, just allocate necessary memory
struct pmsis_device *pmsis_open(const char *name);

struct pmsis_device *pmsis_open_from_conf(void *conf);


int pmsis_close(struct pmsis_device *device);

// ioctl like mechanism
uint32_t pmsis_ioctl(struct pmsis_device *device, uint32_t func_id, void *arg);

// Generic write and read functions:
// write or read to devices (spi, i2s, (hyper)flash...)
// might be null for devices which are not concerned
uint32_t pmsis_write(struct pmsis_device *device, uintptr_t size,
        const void *addr, const void *buffer);

uint32_t pmsis_read(struct pmsis_device *device, uintptr_t size,
        const void *addr, const void *buffer);

#endif
