---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1786376008 14
1786376013 14
1786376018 14
1786376023 14
1786376028 14
1786376033 14
1786376038 9
1786376043 9
1786376048 9
1786376053 9
1786376058 9
1786376063 9
1786376068 9
1786376073 9
1786376078 9
1786376083 9
1786376088 9
1786376093 9
1786376098 9
1786376103 9
```
</details>

---

