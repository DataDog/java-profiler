---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 16:54:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 435 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 59-79 cores)</summary>

```
1778186903 61
1778186908 61
1778186913 59
1778186918 59
1778186923 61
1778186928 61
1778186933 61
1778186938 61
1778186943 61
1778186948 61
1778186953 61
1778186958 59
1778186963 59
1778186968 59
1778186973 61
1778186978 61
1778186983 61
1778186988 61
1778186993 74
1778186998 74
```
</details>

---

