---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:27:58 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 28-44 cores)</summary>

```
1786454500 44
1786454505 44
1786454510 44
1786454515 44
1786454520 40
1786454525 40
1786454530 28
1786454535 28
1786454540 28
1786454545 28
1786454550 28
1786454555 28
1786454560 28
1786454565 28
1786454570 28
1786454575 28
1786454580 28
1786454585 28
1786454590 28
1786454595 28
```
</details>

---

