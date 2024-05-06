/*
 * Copyright (c) 2024 INESC-ID, Instituto Superior Técnico, Universidade de Lisboa
 * Created by Tiago Rocha <tiagolopesrocha@inesc-id.pt>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sbi/sbi_types.h>

#define SBI_EBS_CTR_MAX 32

int sbi_ebs_set_event(uint64_t cval, uint64_t cidx);
int sbi_ebs_set_threshold(uint64_t cval, uint64_t cidx);
int sbi_ebs_set_counter(uint64_t cval, uint64_t cidx);
int sbi_ebs_set_maddr(uint64_t cval);
int sbi_ebs_set_cfg(uint64_t cval);
int sbi_ebs_get_event(uint64_t cidx, unsigned long *out_val);
int sbi_ebs_get_threshold(uint64_t cidx, unsigned long *out_val);
int sbi_ebs_get_counter(uint64_t cidx, unsigned long *out_val);
int sbi_ebs_get_maddr(unsigned long *out_val);
int sbi_ebs_get_cfg(unsigned long *out_val);
