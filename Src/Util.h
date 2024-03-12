#pragma once

#define GET_REG_FIELD(reg, offset, mask) ((reg & mask) >> offset)
