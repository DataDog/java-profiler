---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-22 11:34:56 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 59-69 cores)</summary>

```
1790090858 61
1790090863 61
1790090868 61
1790090873 61
1790090878 61
1790090883 61
1790090888 61
1790090893 61
1790090898 61
1790090903 61
1790090908 61
1790090913 61
1790090918 61
1790090923 61
1790090928 61
1790090933 61
1790090938 59
1790090943 59
1790090948 59
1790090953 59
```
</details>

---

