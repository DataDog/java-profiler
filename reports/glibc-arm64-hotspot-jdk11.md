---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 08:17:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 15 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 31-48 cores)</summary>

```
1793362397 48
1793362402 36
1793362407 36
1793362412 36
1793362417 36
1793362422 31
1793362427 31
1793362432 31
1793362437 31
1793362442 31
1793362447 31
1793362452 31
1793362457 31
1793362462 31
1793362467 31
1793362472 31
1793362477 31
1793362482 36
1793362487 36
1793362492 36
```
</details>

---

