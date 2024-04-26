#pragma once

#define GET_REG_FIELD(reg, offset, mask) ((reg & mask) >> offset)

//NOTE(tsharpe): Beware both mask and value are shifted by offset, making this difficult to really use with CMSIS
#define SET_REG_FIELD(reg, offset, mask, value)\
do\
{\
	uint32_t temp;\
	temp = reg;\
	temp &= ~((mask) << (offset));\
	temp |= ((value) << (offset));\
	reg = temp;\
} while (false)
