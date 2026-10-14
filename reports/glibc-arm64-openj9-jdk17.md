---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 10:47:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 11 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1791988935 25
1791988940 25
1791988945 25
1791988950 25
1791988955 25
1791988960 25
1791988965 25
1791988970 25
1791988975 25
1791988980 25
1791988985 25
1791988990 25
1791988995 25
1791989000 25
1791989005 25
1791989010 25
1791989015 25
1791989020 38
1791989025 38
1791989030 38
```
</details>

---

