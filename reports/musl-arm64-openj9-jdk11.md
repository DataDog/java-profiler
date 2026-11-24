---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 10:25:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 14 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795533664 34
1795533669 34
1795533674 34
1795533679 34
1795533684 34
1795533689 34
1795533694 34
1795533699 34
1795533704 34
1795533709 34
1795533714 34
1795533719 34
1795533724 34
1795533729 34
1795533734 34
1795533739 34
1795533744 34
1795533749 34
1795533754 34
1795533759 34
```
</details>

---

