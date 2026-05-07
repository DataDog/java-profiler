---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-07 16:54:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 81-89 cores)</summary>

```
1778186898 87
1778186903 89
1778186908 89
1778186913 89
1778186918 89
1778186923 89
1778186928 89
1778186933 89
1778186938 89
1778186943 81
1778186948 81
1778186953 81
1778186958 81
1778186963 81
1778186968 84
1778186973 84
1778186978 84
1778186983 86
1778186988 86
1778186993 86
```
</details>

---

