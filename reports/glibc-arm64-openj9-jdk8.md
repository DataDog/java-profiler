---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-13 00:57:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1786596785 51
1786596790 51
1786596795 51
1786596800 51
1786596805 51
1786596810 51
1786596815 51
1786596820 51
1786596825 51
1786596830 51
1786596835 51
1786596840 51
1786596845 56
1786596850 56
1786596855 56
1786596860 56
1786596865 56
1786596870 56
1786596875 56
1786596880 56
```
</details>

---

