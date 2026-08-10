---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 01:03:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 11 |
| Allocations | 158 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1786337955 40
1786337960 40
1786337965 40
1786337970 40
1786337975 40
1786337980 40
1786337985 40
1786337990 40
1786337995 40
1786338000 40
1786338005 40
1786338010 40
1786338015 40
1786338020 40
1786338025 40
1786338030 40
1786338035 40
1786338040 40
1786338045 40
1786338050 48
```
</details>

---

