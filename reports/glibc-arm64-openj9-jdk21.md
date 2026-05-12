---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 20:52:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778546978 64
1778546983 64
1778546988 64
1778546993 64
1778546998 64
1778547003 64
1778547008 64
1778547013 64
1778547018 64
1778547023 64
1778547028 64
1778547033 64
1778547038 64
1778547043 64
1778547048 64
1778547053 64
1778547058 64
1778547063 64
1778547068 64
1778547073 64
```
</details>

---

