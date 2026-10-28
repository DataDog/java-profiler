---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 07:48:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (2 unique values: 21-29 cores)</summary>

```
1793187894 21
1793187899 21
1793187904 21
1793187909 21
1793187914 21
1793187919 21
1793187924 21
1793187929 21
1793187934 21
1793187939 29
1793187944 29
1793187949 29
1793187954 29
1793187959 29
1793187964 29
1793187969 29
1793187974 29
1793187979 29
1793187984 29
1793187989 29
```
</details>

---

