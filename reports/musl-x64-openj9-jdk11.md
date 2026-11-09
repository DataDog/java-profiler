---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-08 20:29:11 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 27-31 cores)</summary>

```
1794187460 31
1794187465 31
1794187470 31
1794187475 31
1794187480 31
1794187485 31
1794187490 31
1794187495 31
1794187500 29
1794187505 29
1794187510 29
1794187515 29
1794187520 29
1794187525 29
1794187530 29
1794187535 29
1794187540 29
1794187545 29
1794187550 27
1794187555 27
```
</details>

---

