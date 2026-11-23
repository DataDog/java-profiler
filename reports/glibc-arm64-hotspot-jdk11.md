---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 09:03:26 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 29 |
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
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (5 unique values: 29-44 cores)</summary>

```
1795442312 41
1795442317 41
1795442322 41
1795442327 41
1795442332 41
1795442337 36
1795442342 36
1795442347 36
1795442352 36
1795442357 36
1795442362 36
1795442368 36
1795442373 36
1795442378 40
1795442383 40
1795442388 44
1795442393 44
1795442398 44
1795442403 44
1795442408 44
```
</details>

---

