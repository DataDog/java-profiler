---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-15 09:27:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 26-36 cores)</summary>

```
1792070575 26
1792070580 26
1792070585 26
1792070590 26
1792070595 26
1792070600 26
1792070605 26
1792070610 26
1792070615 26
1792070620 26
1792070625 36
1792070630 36
1792070635 31
1792070640 31
1792070645 31
1792070650 31
1792070655 31
1792070660 31
1792070665 31
1792070670 31
```
</details>

---

