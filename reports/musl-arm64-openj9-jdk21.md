---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:25:15 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (6 unique values: 34-42 cores)</summary>

```
1794831575 42
1794831580 42
1794831585 39
1794831590 39
1794831595 39
1794831600 39
1794831605 35
1794831610 35
1794831615 35
1794831620 35
1794831625 34
1794831630 34
1794831635 39
1794831640 39
1794831645 39
1794831650 38
1794831655 38
1794831660 38
1794831665 38
1794831670 38
```
</details>

---

