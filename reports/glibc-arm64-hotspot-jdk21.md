---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 07:29:46 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 11 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1791372358 36
1791372363 31
1791372368 31
1791372373 31
1791372378 31
1791372383 31
1791372388 31
1791372393 31
1791372398 31
1791372403 31
1791372408 31
1791372413 31
1791372418 31
1791372423 31
1791372428 31
1791372433 36
1791372438 36
1791372443 36
1791372448 36
1791372453 36
```
</details>

---

