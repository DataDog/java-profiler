---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:27:11 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 12 |
| Allocations | 207 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1794428565 20
1794428570 20
1794428575 20
1794428580 20
1794428585 20
1794428590 20
1794428595 20
1794428600 20
1794428605 20
1794428610 22
1794428615 22
1794428620 22
1794428625 22
1794428630 22
1794428635 22
1794428640 22
1794428645 22
1794428650 22
1794428655 22
1794428660 22
```
</details>

---

