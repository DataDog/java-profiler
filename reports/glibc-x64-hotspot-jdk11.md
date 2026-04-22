---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-22 13:39:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 26-64 cores)</summary>

```
1776879185 26
1776879190 28
1776879195 28
1776879200 28
1776879205 28
1776879210 64
1776879215 64
1776879220 33
1776879225 33
1776879230 33
1776879235 33
1776879240 33
1776879245 33
1776879250 33
1776879255 33
1776879260 33
1776879266 33
1776879271 33
1776879276 33
1776879281 33
```
</details>

---

