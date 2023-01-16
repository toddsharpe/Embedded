#pragma once

#define SET_REG_FIELD(reg, offset, mask, value)\
	do\
	{\
		uint32_t temp;\
		temp = reg;\
		temp &= ~((mask) << (offset));\
		temp |= ((value) << (offset));\
		reg = temp;\
	} while (false)

#define GET_REG_FIELD(reg, offset, mask) ((reg & mask) >> offset)