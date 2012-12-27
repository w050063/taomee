/*
 * =====================================================================================
 *
 *       Filename:  global.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2011 01:22:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ian (), ian@taomee.com
 *        Company:  Taomee.Ltd
 *
 * =====================================================================================
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "CChatCheck.h"
#include <algorithm>
#include <string>
#include "dirty_word.h"
#include <mmseg/bsd_getopt.h>
#include <mmseg/SegmenterManager.h>
#include <mmseg/csr_utils.h>
using namespace css;

const int max_game_id = 100;
extern Cdirty_word* g_dirty_word;

extern std::map<uint32_t, CChatCheck*> game_chat_check;

typedef struct timer_head {
    list_head_t timer_list;
}timer_head_t;
extern timer_head_t g_events;
extern SegmenterManager g_seg_mgr;

#endif
