---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 14:42:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 11 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 26-56 cores)</summary>

```
1786127895 26
1786127900 26
1786127905 26
1786127910 26
1786127915 26
1786127920 56
1786127925 56
1786127930 56
1786127935 56
1786127940 56
1786127945 56
1786127950 56
1786127955 56
1786127960 56
1786127965 56
1786127970 56
1786127975 56
1786127980 56
1786127985 56
1786127990 56
```
</details>

---

