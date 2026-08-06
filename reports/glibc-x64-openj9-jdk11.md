---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 08:59:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 42-66 cores)</summary>

```
1786020967 42
1786020972 42
1786020977 50
1786020982 50
1786020987 50
1786020992 50
1786020997 50
1786021002 50
1786021007 50
1786021012 64
1786021017 64
1786021022 64
1786021027 66
1786021032 66
1786021037 66
1786021042 66
1786021047 66
1786021052 66
1786021057 66
1786021062 66
```
</details>

---

