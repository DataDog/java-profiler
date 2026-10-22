---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:32:08 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 53-93 cores)</summary>

```
1792672040 93
1792672045 93
1792672050 93
1792672055 93
1792672060 93
1792672065 93
1792672070 93
1792672075 93
1792672080 93
1792672085 93
1792672090 93
1792672095 93
1792672100 93
1792672105 93
1792672110 93
1792672115 93
1792672120 53
1792672125 53
1792672130 53
1792672135 53
```
</details>

---

