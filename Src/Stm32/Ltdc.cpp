// RM0385 Reference Manual

#include "Stm32/Ltdc.h"
#include "Util.h"

#include <stm32f7xx.h>
#include <cstdint>

namespace Stm32
{
	Ltdc::Layer::Layer(LTDC_Layer_TypeDef* layer) :
		m_layer(layer)
	{
	}

	//TODO(tsharpe): Extend method to take a rectangle of the viewport and modify WHPCR/WVPCR accordingly
	//RM0385 18.6: All layer’s registers are shadowed. Once a register is written, it must not be modified
	//again before the reload has been done. Thus, a new write to the same register overrides the  previous configuration if not yet reloaded
	//NOTE(tsharpe): In practice, this means to set all properties of a layer before enabling it, and then immediately shadow load the LTDC before its enabled
	void Ltdc::Layer::Init(Graphics::FrameBuffer& framebuffer)
	{
		//Frame buffer address
		m_layer->CFBAR = (uint32_t)framebuffer.GetBuffer();
		
		//Set color type
		//TODO(tsharpe): get from framebuffer
		MODIFY_REG(m_layer->PFCR, LTDC_LxPFCR_PF, 0b010 << LTDC_LxPFCR_PF_Pos);

		//Set alpha value
		m_layer->CACR = 255;

		//Color frame buffer line number
		m_layer->CFBLNR = framebuffer.GetHeight();

		//Frame buffer length
		const size_t lineLength = framebuffer.GetWidth() * framebuffer.PixelSize();
		LTDC_Layer1->CFBLR = (((lineLength) << LTDC_LxCFBLR_CFBP_Pos) | (lineLength + 3));
	}

	void Ltdc::Layer::Enable()
	{
		SET_BIT(m_layer->CR, LTDC_LxCR_LEN);
	}
	
	Ltdc::Ltdc(const LtdcConfig& config) :
	 	Layers({ LTDC_Layer1, LTDC_Layer2 }),
		m_ltdc(LTDC),
		m_config(config)
	{

	}

	void Ltdc::Init()
	{	
		//Sync size config
		MODIFY_REG(LTDC->SSCR, LTDC_SSCR_VSH, (m_config.Vsync - 1) << LTDC_SSCR_VSH_Pos);
		MODIFY_REG(LTDC->SSCR, LTDC_SSCR_HSW, (m_config.Hsync - 1) << LTDC_SSCR_HSW_Pos);

		//Back porch config
		const uint32_t avbp = m_config.Vsync + m_config.Vbp - 1;
		MODIFY_REG(LTDC->BPCR, LTDC_BPCR_AVBP, avbp << LTDC_BPCR_AVBP_Pos);
		const uint32_t ahbp = m_config.Hsync + m_config.Hbp - 1;
		MODIFY_REG(LTDC->BPCR, LTDC_BPCR_AHBP, ahbp << LTDC_BPCR_AHBP_Pos);

		//Active width config
		const uint32_t aah = m_config.DisplayHeight + avbp;
		MODIFY_REG(LTDC->AWCR, LTDC_AWCR_AAH, aah << LTDC_AWCR_AAH_Pos);
		const uint32_t aaw = m_config.DisplayWidth + ahbp;
		MODIFY_REG(LTDC->AWCR, LTDC_AWCR_AAW, aaw << LTDC_AWCR_AAW_Pos);

		//Total width config
		MODIFY_REG(LTDC->TWCR, LTDC_TWCR_TOTALH, (aah + m_config.Vfp) << LTDC_TWCR_TOTALH_Pos);
		MODIFY_REG(LTDC->TWCR, LTDC_TWCR_TOTALW, (aaw + m_config.Hfp) << LTDC_TWCR_TOTALW_Pos);

		//Initialize layers
		for (auto& layer : { LTDC_Layer1, LTDC_Layer2 })
		{
			//Window horizontal position config
			layer->WHPCR = (((aaw) << LTDC_LxWHPCR_WHSPPOS_Pos) | (ahbp + 1));

			//Window vertical position config
			layer->WVPCR = (((aah) << LTDC_LxWVPCR_WVSPPOS_Pos) | (aah + 1));
		}

		//Background color
		LTDC->BCCR = 0x00;
	}

	void Ltdc::Enable()
	{
		//Shadow reload config
		//NOTE(tsharpe): The "correct" value here is unclear, using VBR but maybe consider IMR?
		LTDC->SRCR = LTDC_SRCR_VBR;
		SET_BIT(LTDC->GCR, LTDC_GCR_LTDCEN);
	}
}

