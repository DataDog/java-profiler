---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:47:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 31-73 cores)</summary>

```
1795531348 31
1795531353 31
1795531358 31
1795531363 31
1795531368 31
1795531373 31
1795531378 31
1795531383 52
1795531388 52
1795531393 52
1795531398 52
1795531403 52
1795531408 52
1795531413 52
1795531418 52
1795531423 50
1795531428 50
1795531433 50
1795531438 50
1795531443 50
```
</details>

---

