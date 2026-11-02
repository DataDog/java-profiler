---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:41:17 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 12 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 67-68 cores)</summary>

```
1793633797 68
1793633802 68
1793633807 68
1793633812 68
1793633817 68
1793633822 68
1793633827 68
1793633832 68
1793633837 67
1793633842 67
1793633847 67
1793633852 67
1793633857 67
1793633862 67
1793633867 67
1793633872 67
1793633877 67
1793633882 67
1793633887 67
1793633892 67
```
</details>

---

