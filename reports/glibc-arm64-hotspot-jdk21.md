---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 11:46:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1786376388 53
1786376393 53
1786376398 53
1786376403 53
1786376408 53
1786376413 64
1786376418 64
1786376423 64
1786376428 64
1786376433 51
1786376438 51
1786376443 51
1786376448 51
1786376453 46
1786376458 46
1786376463 46
1786376468 46
1786376473 46
1786376478 46
1786376483 46
```
</details>

---

