---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 10 |
| Allocations | 186 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794355430 46
1794355435 46
1794355440 46
1794355445 46
1794355450 46
1794355455 46
1794355460 46
1794355465 51
1794355470 51
1794355475 51
1794355480 51
1794355485 51
1794355490 51
1794355495 51
1794355501 51
1794355506 51
1794355511 51
1794355516 51
1794355521 51
1794355526 51
```
</details>

---

