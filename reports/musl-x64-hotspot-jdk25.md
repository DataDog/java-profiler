---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-16 10:55:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 20-27 cores)</summary>

```
1776350952 27
1776350957 27
1776350962 27
1776350967 27
1776350972 27
1776350977 27
1776350982 27
1776350987 27
1776350992 27
1776350997 27
1776351002 27
1776351007 27
1776351012 27
1776351017 27
1776351022 25
1776351027 25
1776351033 25
1776351038 20
1776351043 20
1776351048 20
```
</details>

---

