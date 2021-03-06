#!/usr/bin/env python
# ==============================================================================
#          \file   seg.py
#        \author   chenghuige  
#          \date   2014-03-01 13:32:30.259515
#   \Description  
# ==============================================================================

import sys,os
from libgezi import *

LogHelper.set_level(4)

seg_init2()

sep = '\t'
sep_seg = '$#$'
for line in sys.stdin:
	try:
		l = line.strip().split(sep)
		label = l[0]
		title = l[3] 
		content = l[4]
		result = ''
		if is_thread(title):
			result += segment2(title, sep_seg)
			result += sep_seg
		content = strip_html(content)
		result += segment2(content, sep_seg)
		print sep.join([label, result])
	except Exception:
		continue

