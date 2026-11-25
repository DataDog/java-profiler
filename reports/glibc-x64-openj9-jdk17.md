---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:28:30 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 63-72 cores)</summary>

```
1795630962 63
1795630967 63
1795630972 63
1795630977 63
1795630982 63
1795630987 63
1795630992 63
1795630997 63
1795631002 63
1795631007 63
1795631012 72
1795631017 72
1795631022 72
1795631027 72
1795631032 72
1795631037 72
1795631042 72
1795631047 72
1795631052 72
1795631057 72
```
</details>

---

