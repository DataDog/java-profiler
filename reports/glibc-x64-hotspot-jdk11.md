---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 06:13:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787134031 96
1787134036 96
1787134041 96
1787134046 96
1787134051 96
1787134056 96
1787134061 96
1787134066 96
1787134071 96
1787134076 96
1787134081 96
1787134086 96
1787134091 96
1787134096 96
1787134101 96
1787134106 94
1787134111 94
1787134116 94
1787134121 94
1787134126 94
```
</details>

---

