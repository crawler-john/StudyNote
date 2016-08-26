/*
 * vim:ts=4:sw=4
 * =====================================================================================
 *       
 *       Filename:  setmmu_table.c
 *
 *    Description:  setmmu_table.c
 *
 *        Version:  1.0
 *        Created:  08/30/2012 12:38:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  FH (@), fenghua@tarena.com.cn
 *   Organization:   Copyright (c) 2012, tarena
 *
 * =====================================================================================
 */
#define FL_SECTION_ENTRY(base,ap,d,c,b)  \
    ((base << 20) | (ap << 10) | (d << 5) | (1<<4) | (c << 3) | (b << 2) | (1<<1))

void set_mmu_table(unsigned int *addr)
{
    int i;
    unsigned int base;

	base = 0x200;
    for (i = 0; i < 0x100; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 0, 0);
        base++;
    }

    for (i = 0x100; i < 0x200; i++)
    {
        addr[i] = 0;
    }

    base = 0x200;
    for (i = 0x200; i < 0x600; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 1, 1);
        base++;
    }

    for (i = 0x600; i < 0x800; i++)
    {
        addr[i] = 0;
    }

    base = 0x800;
    for (i = 0x800; i < 0xB00; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 0, 0);
        base++;
    }

    base = 0xB00;
    for (i = 0xB00; i < 0xC00; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 0, 0);
        base++;
    }

    base = 0x200;
    for (i = 0xC00; i < 0xD00; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 1, 1);
        base++;
    }

    base = 0xD00;
    for (i = 0xD00; i < 0x1000; i++)
    {
        addr[i] = FL_SECTION_ENTRY(base, 3, 0, 0, 0);
        base++;
    }

}
