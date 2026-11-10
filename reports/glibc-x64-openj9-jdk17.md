---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 52-60 cores)</summary>

```
1794340131 60
1794340136 60
1794340141 60
1794340146 60
1794340151 60
1794340156 60
1794340161 60
1794340166 60
1794340171 60
1794340176 60
1794340181 58
1794340186 58
1794340191 58
1794340196 58
1794340201 58
1794340206 58
1794340211 54
1794340216 54
1794340221 54
1794340226 52
```
</details>

---

