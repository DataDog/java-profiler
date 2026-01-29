---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 21.37/sec |
| Health Score | 1336% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1093 |
| Sample Rate | 36.43/sec |
| Health Score | 2277% |
| Threads | 13 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 37-43 cores)</summary>

```
1769702695 39
1769702700 37
1769702705 37
1769702710 43
1769702715 43
1769702720 43
1769702725 43
1769702730 43
1769702735 43
1769702740 43
1769702745 43
1769702750 43
1769702755 43
1769702760 43
1769702765 43
1769702770 43
1769702775 43
1769702780 43
1769702785 43
1769702790 43
```
</details>

---

