---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:59:59 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (2 unique values: 7-32 cores)</summary>

```
1786020948 7
1786020953 7
1786020958 7
1786020963 7
1786020968 7
1786020973 7
1786020978 7
1786020983 32
1786020988 32
1786020993 7
1786020998 7
1786021003 7
1786021008 7
1786021013 7
1786021018 7
1786021023 7
1786021028 7
1786021034 7
1786021039 7
1786021044 7
```
</details>

---

