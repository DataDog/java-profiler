---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 11:23:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 21-32 cores)</summary>

```
1791299893 32
1791299898 32
1791299903 32
1791299908 32
1791299913 32
1791299918 32
1791299923 32
1791299928 32
1791299933 32
1791299938 32
1791299943 32
1791299948 32
1791299953 32
1791299958 32
1791299963 32
1791299968 32
1791299973 32
1791299978 23
1791299983 23
1791299988 21
```
</details>

---

