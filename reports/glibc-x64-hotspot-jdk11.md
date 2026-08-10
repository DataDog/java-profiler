---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 16:31:52 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1786393545 36
1786393550 36
1786393555 38
1786393560 38
1786393565 36
1786393570 36
1786393575 36
1786393580 36
1786393585 36
1786393590 36
1786393595 36
1786393600 36
1786393605 36
1786393610 36
1786393615 36
1786393620 36
1786393625 36
1786393630 36
1786393635 36
1786393640 36
```
</details>

---

