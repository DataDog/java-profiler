---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 00:59:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 73-78 cores)</summary>

```
1790830486 73
1790830491 73
1790830496 73
1790830501 73
1790830506 73
1790830511 73
1790830516 73
1790830521 73
1790830526 73
1790830531 78
1790830536 78
1790830541 78
1790830546 78
1790830551 78
1790830556 78
1790830561 78
1790830566 78
1790830571 78
1790830576 78
1790830581 76
```
</details>

---

