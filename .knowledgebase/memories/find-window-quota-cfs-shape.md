---
id: find-window-quota-cfs-shape
title: measurement windows under CPU quota must span several CFS periods or the delivered-share reading aliases
kind: finding
tags: [cfs, quota, window, benchmark, load, testing]
applies_to: []
source: native-safety-hypothesis-loop/find-window-quota-cfs-shape
status: active
recorded: 2026-11-11
valid_at: 2026-11-11
---


At a binding CPU quota, CFS delivers CPU in period quanta: windows shorter than
a few periods alias a variable number of quanta and scatter the apparent
delivered share (observed ratio medians 0.73 down to 0.38 as the window grew
from 99 ms to 999 ms), while windows spanning at least 3 periods converge to the
quota share. Any quota- or stall-ratio comparison needs window-length control
aligned to CFS periods, and sampling cadences (e.g. a 5 s memory sampler) sit
far above this aliasing regime.
