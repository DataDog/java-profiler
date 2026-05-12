---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-12 02:56:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 328 |
| Sample Rate | 5.47/sec |
| Health Score | 342% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 41-48 cores)</summary>

```
1778568800 48
1778568805 43
1778568810 43
1778568815 43
1778568820 43
1778568825 43
1778568830 43
1778568835 43
1778568840 43
1778568845 43
1778568850 43
1778568855 43
1778568860 43
1778568865 43
1778568870 43
1778568875 43
1778568880 43
1778568885 41
1778568890 41
1778568895 41
```
</details>

---

