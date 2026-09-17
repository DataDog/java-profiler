---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 16:56:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 7-7 cores)</summary>

```
1789677953 7
1789677958 7
1789677963 7
1789677968 7
1789677973 7
1789677978 7
1789677983 7
1789677988 7
1789677993 7
1789677998 7
1789678003 7
1789678008 7
1789678013 7
1789678018 7
1789678023 7
1789678028 7
1789678033 7
1789678038 7
1789678043 7
1789678048 7
```
</details>

---

