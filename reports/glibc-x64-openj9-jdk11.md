---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 13:18:12 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1066 |
| Sample Rate | 17.77/sec |
| Health Score | 1111% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 89-93 cores)</summary>

```
1792516360 91
1792516365 91
1792516370 91
1792516375 91
1792516380 91
1792516385 91
1792516390 91
1792516395 91
1792516400 91
1792516405 93
1792516410 93
1792516415 93
1792516420 93
1792516425 91
1792516430 91
1792516435 91
1792516440 89
1792516445 89
1792516450 89
1792516455 89
```
</details>

---

