---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-06 10:08:45 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 27-30 cores)</summary>

```
1791295329 29
1791295334 29
1791295339 29
1791295344 27
1791295349 27
1791295354 27
1791295359 30
1791295364 30
1791295369 30
1791295374 30
1791295379 30
1791295384 30
1791295389 30
1791295394 30
1791295399 28
1791295404 28
1791295409 28
1791295414 28
1791295419 28
1791295424 28
```
</details>

---

