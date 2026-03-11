---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 09:08:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1773234088 32
1773234093 32
1773234098 32
1773234103 32
1773234108 32
1773234113 32
1773234118 32
1773234123 32
1773234128 32
1773234133 32
1773234138 30
1773234143 30
1773234148 30
1773234153 30
1773234158 32
1773234163 32
1773234168 32
1773234173 32
1773234178 32
1773234183 32
```
</details>

---

