---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 05:49:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1778579068 39
1778579073 39
1778579078 39
1778579083 39
1778579088 39
1778579093 39
1778579098 39
1778579103 39
1778579108 39
1778579113 39
1778579118 39
1778579123 44
1778579128 44
1778579133 42
1778579138 42
1778579143 42
1778579148 42
1778579153 42
1778579158 42
1778579163 42
```
</details>

---

