---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 06:25:15 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794914420 51
1794914425 51
1794914430 51
1794914435 51
1794914440 51
1794914445 46
1794914450 46
1794914455 46
1794914460 46
1794914465 46
1794914470 46
1794914475 46
1794914480 46
1794914485 46
1794914490 46
1794914495 46
1794914500 46
1794914505 46
1794914510 46
1794914515 46
```
</details>

---

