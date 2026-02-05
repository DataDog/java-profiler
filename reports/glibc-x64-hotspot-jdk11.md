---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-05 05:23:30 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (4 unique values: 59-64 cores)</summary>

```
1770286704 59
1770286709 59
1770286714 59
1770286719 59
1770286724 59
1770286729 59
1770286734 59
1770286739 59
1770286745 59
1770286750 59
1770286755 59
1770286760 59
1770286765 64
1770286770 64
1770286775 64
1770286780 64
1770286785 64
1770286790 64
1770286795 64
1770286800 62
```
</details>

---

