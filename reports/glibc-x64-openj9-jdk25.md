---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-11 10:47:07 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 10 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 12 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 49-68 cores)</summary>

```
1773240126 49
1773240131 49
1773240136 49
1773240141 49
1773240146 49
1773240151 49
1773240156 49
1773240161 66
1773240166 66
1773240171 66
1773240176 66
1773240181 68
1773240186 68
1773240191 68
1773240196 66
1773240201 66
1773240206 63
1773240211 63
1773240216 63
1773240221 63
```
</details>

---

