---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 09:29:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 20-27 cores)</summary>

```
1776691535 27
1776691540 27
1776691545 27
1776691550 27
1776691555 27
1776691560 27
1776691565 27
1776691570 27
1776691575 27
1776691580 27
1776691585 27
1776691590 27
1776691595 27
1776691600 27
1776691605 27
1776691610 27
1776691615 27
1776691620 27
1776691625 25
1776691630 25
```
</details>

---

