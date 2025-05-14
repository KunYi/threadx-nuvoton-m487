#include "NuMicro.h"

/*
 * IP101GR, Strapping configuration
 * RMII mode with 25MHz Crystal
 * PHY Address is 5'd1
 */

#define IP101GR_ADDR 	(1)

static int mdioWrite(uint32_t u32Addr, uint32_t u32Reg, uint32_t u32Data);
static int mdioRead(uint32_t u32Addr, uint32_t u32Reg, uint32_t *u32Data);


static int mdioWrite(uint32_t u32Addr, uint32_t u32Reg, uint32_t u32Data)
{
    /* From preamble to idle is 64-bit transfer, MDC shouldn't be slower than 1MHz */
    uint32_t u32Delay = SystemCoreClock / 1000000 * 64;
    /* Set data register */
    EMAC->MIIMDAT = u32Data ;
    /* Set PHY address, PHY register address, busy bit and write bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << EMAC_MIIMCTL_PHYADDR_Pos) | EMAC_MIIMCTL_BUSY_Msk |
    			EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;

    /* Wait write complete by polling busy bit. */
    while ((EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk) && (--u32Delay))
    {
        ;
    }

    /* Timeout */
    return (u32Delay > 0) ? 0 : -1;
}

static int mdioRead(uint32_t u32Addr, uint32_t u32Reg, uint32_t *u32Data)
{
    /* From preamble to idle is 64-bit transfer, MDC shouldn't be slower than 1MHz */
    uint32_t u32Delay = SystemCoreClock / 1000000 * 64;
    /* Set PHY address, PHY register address, busy bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << EMAC_MIIMCTL_PHYADDR_Pos) | EMAC_MIIMCTL_BUSY_Msk |
    			EMAC_MIIMCTL_MDCON_Msk;

    /* Wait read complete by polling busy bit */
    while ((EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk) && (--u32Delay))
    {
        ;
    }

    if (u32Delay > 0)
    {
    	/* Get return data */
    	*u32Data = EMAC->MIIMDAT;
	return 0;
    }
    return -1; // timeout
}
