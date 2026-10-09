---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 05:55:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 26-29 cores)</summary>

```
1791539313 29
1791539318 29
1791539323 29
1791539328 29
1791539333 27
1791539338 27
1791539343 27
1791539348 27
1791539353 27
1791539358 27
1791539363 27
1791539368 27
1791539373 27
1791539378 27
1791539383 29
1791539388 29
1791539393 29
1791539398 29
1791539403 29
1791539408 26
```
</details>

---

