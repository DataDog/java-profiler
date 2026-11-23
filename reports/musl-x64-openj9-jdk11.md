---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 808 |
| Sample Rate | 13.47/sec |
| Health Score | 842% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1795449560 32
1795449565 32
1795449570 32
1795449575 32
1795449580 32
1795449585 32
1795449590 32
1795449595 32
1795449600 32
1795449605 32
1795449610 23
1795449615 23
1795449620 23
1795449625 23
1795449630 23
1795449635 23
1795449640 23
1795449645 23
1795449650 23
1795449655 23
```
</details>

---

