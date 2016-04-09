#ifndef NETWORKCODINGHEADER_H_
#define NETWORKCODINGHEADER_H_

#include <stddef.h>

#define OUTERHEADER_SIZE						(sizeof(OuterHeader))
#define GET_BLK_SEQ(pkt)						(*(unsigned short int*)		((unsigned char*)pkt + offsetof(OuterHeader, blk_seq)))
#define GET_BLK_SIZE(pkt)						(*(unsigned char*)			((unsigned char*)pkt + offsetof(OuterHeader, blk_size)))
#define GET_FLAGS(pkt)						(*(unsigned char*)			((unsigned char*)pkt + offsetof(OuterHeader, flags)))
#define GET_SIZE(pkt)							(*(unsigned short int*)		((unsigned char*)pkt + sizeof(OuterHeader) + offsetof(InnerHeader, size)))
#define GET_LAST_INDICATOR(pkt)					(*(unsigned char*)          ((unsigned char*)pkt + sizeof(OuterHeader) + offsetof(InnerHeader, last_indicator)))
#define GET_CODE(pkt)							((unsigned char*)pkt + sizeof(OuterHeader) + offsetof(InnerHeader, codes))
#define GET_PAYLOAD(pkt, max_block_size)		((unsigned char*)pkt + sizeof(OuterHeader) + sizeof(InnerHeader) + (max_block_size-1))
#define HEADER_SIZE(max_block_size)				(sizeof(OuterHeader) + sizeof(InnerHeader) + (max_block_size-1))
#define MAX_PAYLOAD_SIZE(max_block_size)		(1500 - 20 - 8 - HEADER_SIZE(max_block_size))

struct OuterHeader
{
    unsigned short int blk_seq;	/*2*/
    unsigned char blk_size;          /*1*/
    unsigned char flags;               /*1*/
#define FLAGS_END_OF_BLK                  0x1
#define FLAGS_HAS_DATA                      0x2
}__attribute__((packed));

struct InnerHeader
{
    unsigned short int size;          /*2*/
	unsigned char last_indicator;	/*1*/
    unsigned char codes;             /*blk_size*/
}__attribute__((packed));

#endif
