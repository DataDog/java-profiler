---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 05:55:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1791539312 30
1791539317 30
1791539322 30
1791539327 30
1791539332 30
1791539337 30
1791539343 32
1791539348 32
1791539353 32
1791539358 32
1791539363 32
1791539368 30
1791539373 30
1791539378 30
1791539383 30
1791539388 30
1791539393 30
1791539398 30
1791539403 30
1791539408 30
```
</details>

---

