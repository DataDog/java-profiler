---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:41:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 83-89 cores)</summary>

```
1794832715 89
1794832720 89
1794832725 89
1794832730 89
1794832735 89
1794832740 89
1794832745 87
1794832750 87
1794832755 87
1794832760 87
1794832765 89
1794832770 89
1794832775 83
1794832780 83
1794832785 83
1794832790 83
1794832795 83
1794832800 83
1794832805 83
1794832810 83
```
</details>

---

