---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 06:22:05 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1770117435 32
1770117440 32
1770117445 32
1770117450 15
1770117455 15
1770117460 15
1770117465 15
1770117470 15
1770117475 15
1770117480 15
1770117485 15
1770117490 15
1770117495 15
1770117500 15
1770117505 15
1770117510 15
1770117515 15
1770117520 15
1770117525 15
1770117530 15
```
</details>

---

