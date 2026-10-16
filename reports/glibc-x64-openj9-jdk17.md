---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 05:16:14 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 74-89 cores)</summary>

```
1792141914 74
1792141919 74
1792141924 74
1792141929 74
1792141934 89
1792141939 89
1792141944 89
1792141949 89
1792141954 87
1792141959 87
1792141964 87
1792141969 87
1792141974 87
1792141979 87
1792141984 87
1792141989 87
1792141994 87
1792141999 87
1792142004 87
1792142009 87
```
</details>

---

