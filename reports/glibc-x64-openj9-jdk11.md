---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:40:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 65-76 cores)</summary>

```
1794504874 76
1794504879 76
1794504884 67
1794504889 67
1794504894 67
1794504899 67
1794504904 69
1794504909 69
1794504914 69
1794504919 67
1794504924 67
1794504929 67
1794504934 67
1794504939 67
1794504944 67
1794504949 67
1794504954 67
1794504959 67
1794504964 67
1794504969 67
```
</details>

---

