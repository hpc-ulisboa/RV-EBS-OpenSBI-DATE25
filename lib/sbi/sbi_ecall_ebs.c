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

#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_ebs.h>
#include <sbi/sbi_trap.h>

static int sbi_ecall_ebs_handler(unsigned long extid, unsigned long funcid,
								const struct sbi_trap_regs *regs,
								unsigned long *out_val,
								struct sbi_trap_info *out_trap)
{
	int ret = 0;

	switch (funcid) {
	case SBI_EXT_EBS_SET_EVENT:
		ret = sbi_ebs_set_event(regs->a0, regs->a1);
		break;
	case SBI_EXT_EBS_SET_THRESHOLD:
		ret = sbi_ebs_set_threshold(regs->a0, regs->a1);
		break;
	case SBI_EXT_EBS_SET_COUNTER:
		ret = sbi_ebs_set_counter(regs->a0, regs->a1);
		break;
	case SBI_EXT_EBS_SET_MADDR:
		ret = sbi_ebs_set_maddr(regs->a0);
		break;
	case SBI_EXT_EBS_SET_CFG:
		ret = sbi_ebs_set_cfg(regs->a0);
		break;
	case SBI_EXT_EBS_GET_EVENT:
		ret = sbi_ebs_get_event(regs->a1, out_val);
		break;
	case SBI_EXT_EBS_GET_THRESHOLD:
		ret = sbi_ebs_get_threshold(regs->a1, out_val);
		break;
	case SBI_EXT_EBS_GET_COUNTER:
		ret = sbi_ebs_get_counter(regs->a1, out_val);
		break;
	case SBI_EXT_EBS_GET_MADDR:
		ret = sbi_ebs_get_maddr(out_val);
		break;
	case SBI_EXT_EBS_GET_CFG:
		ret = sbi_ebs_get_cfg(out_val);
		break;
	default:
		ret = SBI_ENOTSUPP;
	}

	return ret;
}

static int sbi_ecall_ebs_probe(unsigned long extid, unsigned long *out_val)
{
	/* EBS extension is always enabled*/
	*out_val = 1;
	return 0;
}

struct sbi_ecall_extension ecall_ebs = {
	.extid_start	= SBI_EXT_EBS,
	.extid_end		= SBI_EXT_EBS,
	.handle			= sbi_ecall_ebs_handler,
	.probe			= sbi_ecall_ebs_probe,
};
