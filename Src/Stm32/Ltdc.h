#pragma once

#include "Graphics/FrameBuffer.h"

#include <stm32f746xx.h>
#include <cstddef>
#include <array>

namespace Stm32
{
	//       HSYNC|HBP|WIDTH|HFP
	//VSYNC |
	//VBP   |
	//HEIGHT|        |screen|
	//VFP   |
	struct LtdcConfig
	{
		size_t DisplayWidth;		///LCD PIXEL WIDTH
		size_t DisplayHeight;		//LCD PIXEL HEIGHT
		size_t Hsync;				//Horizontal synchronization
		size_t Hbp;					//Horizontal back porch
		size_t Hfp;					//Horizontal front porch
		size_t Vsync;				//Vertical synchronization
		size_t Vbp;					//Vertical back porch
		size_t Vfp;					//Vertical front porch
	};

	class Ltdc
	{
	public:
		class Layer
		{
		public:
			Layer(LTDC_Layer_TypeDef* layer);
			void Init(Graphics::FrameBuffer& framebuffer);
			void SetSource(Graphics::FrameBuffer& framebuffer);
			void Enable();

		private:
			LTDC_Layer_TypeDef* m_layer;
		};

		Ltdc(const LtdcConfig& config);

		void Init();
		void Enable();

		std::array<Layer, 2> Layers;

	private:
		LTDC_TypeDef* m_ltdc;
		const LtdcConfig& m_config;
	};
}
