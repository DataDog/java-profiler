---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-07 10:19:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 31-43 cores)</summary>

```
1794064580 36
1794064585 36
1794064590 36
1794064595 36
1794064600 36
1794064605 36
1794064610 31
1794064615 31
1794064620 31
1794064625 31
1794064630 31
1794064635 31
1794064640 31
1794064645 31
1794064650 31
1794064655 31
1794064660 43
1794064665 43
1794064670 43
1794064675 43
```
</details>

---

