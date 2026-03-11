---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-11 09:08:01 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 20-27 cores)</summary>

```
1773234129 25
1773234134 25
1773234139 25
1773234144 25
1773234149 25
1773234154 27
1773234159 27
1773234165 27
1773234170 27
1773234175 27
1773234180 27
1773234185 27
1773234190 27
1773234195 27
1773234200 27
1773234205 27
1773234210 27
1773234215 22
1773234220 22
1773234225 20
```
</details>

---

