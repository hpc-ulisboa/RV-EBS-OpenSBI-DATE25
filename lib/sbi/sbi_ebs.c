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

#include <sbi/riscv_asm.h>
#include <sbi/sbi_ebs.h>
#include <sbi/sbi_error.h>
#include <sbi/riscv_encoding.h>

int sbi_ebs_set_event(uint64_t cval, uint64_t cidx)
{
	if (cidx < 3 || cidx >= SBI_EBS_CTR_MAX)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	csr_write_num(CSR_MHPMEVENT3 + cidx - 3, cval & 0xFFFFFFFF);
	csr_write_num(CSR_MHPMEVENT3H + cidx - 3, cval >> BITS_PER_LONG);
#else
	csr_write_num(CSR_MHPMEVENT3 + cidx - 3, cval);
#endif
	return SBI_OK;
}

int sbi_ebs_set_threshold(uint64_t cval, uint64_t cidx)
{
	if (cidx >= SBI_EBS_CTR_MAX || cidx == 1)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	csr_write_num(CSR_MHPMTHRESHOLDCYCLE + cidx, cval & 0xFFFFFFFF);
	csr_write_num(CSR_MHPMTHRESHOLDCYCLEH + cidx, cval >> BITS_PER_LONG);
#else
	csr_write_num(CSR_MHPMTHRESHOLDCYCLE + cidx, cval);
#endif
	return SBI_OK;
}

int sbi_ebs_set_counter(uint64_t cval, uint64_t cidx)
{
	if (cidx < 3 || cidx >= SBI_EBS_CTR_MAX)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	csr_write_num(CSR_MHPMCOUNTER3 + cidz - 3, cval & 0xFFFFFFFF);
	csr_write_num(CSR_MHPMCOUNTER3H + cidx - 3,, cval >> BITS_PER_LONG);
#else
	csr_write_num(CSR_MHPMCOUNTER3 + cidx - 3, cval);
#endif
	return SBI_OK;
}

int sbi_ebs_set_maddr(uint64_t cval)
{
	csr_write_num(CSR_MHPM_MADDR, cval);
	return SBI_OK;
}

int sbi_ebs_set_cfg(uint64_t cval)
{
	csr_write_num(CSR_MHPM_EBS_CFG, cval);
	return SBI_OK;
}

int sbi_ebs_get_event(uint64_t cidx, unsigned long *out_val)
{
		if (cidx < 3 || cidx >= SBI_EBS_CTR_MAX)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	uint32_t temp, temph = 0;

	temp = csr_read_num(CSR_MHPMEVENT3 + cidx - 3);
	temph = csr_read_num(CSR_MHPMEVENT3H + cidx - 3);
	*out_val = (unsigned long)((uint64_t)(temph << 32) | (uint64_t)temp);
#else
	*out_val = csr_read_num(CSR_MHPMEVENT3 + cidx - 3);
#endif
	return SBI_OK;
}

int sbi_ebs_get_threshold(uint64_t cidx, unsigned long *out_val)
{
	if (cidx >= SBI_EBS_CTR_MAX || cidx == 1)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	uint32_t temp, temph = 0;

	temp = csr_read_num(CSR_MHPMTHRESHOLDCYCLE + cidx);
	temph = csr_read_num(CSR_MHPMTHRESHOLDCYCLEH + cidx);
	*out_val = (unsigned long)((uint64_t)(temph << 32) | (uint64_t)temp);
#else
	*out_val = csr_read_num(CSR_MHPMTHRESHOLDCYCLE + cidx);
#endif
	return SBI_OK;
}

int sbi_ebs_get_counter(uint64_t cidx, unsigned long *out_val)
{
		if (cidx < 3 || cidx >= SBI_EBS_CTR_MAX)
		return SBI_EINVAL;
#if __riscv_xlen == 32
	uint32_t temp, temph = 0;

	temp = csr_read_num(CSR_MHPMCOUNTER3 + cidx - 3);
	temph = csr_read_num(CSR_MHPMCOUNTER3H + cidx - 3);
	*out_val = (unsigned long)((uint64_t)(temph << 32) | (uint64_t)temp);
#else
	*out_val = csr_read_num(CSR_MHPMCOUNTER3 + cidx - 3);
#endif
	return SBI_OK;
}

int sbi_ebs_get_maddr(unsigned long *out_val) // TODO_INESC: This doesn't work for riscv32
{
	*out_val = csr_read_num(CSR_MHPM_MADDR);
	return SBI_OK;
}

int sbi_ebs_get_cfg(unsigned long *out_val)
{
	*out_val = csr_read_num(CSR_MHPM_EBS_CFG);
	return SBI_OK;
}
