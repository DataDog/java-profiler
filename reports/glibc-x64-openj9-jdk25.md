---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-26 08:57:44 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 34-81 cores)</summary>

```
1793019080 81
1793019085 81
1793019090 34
1793019095 34
1793019100 34
1793019105 34
1793019110 34
1793019115 34
1793019120 34
1793019125 34
1793019130 34
1793019135 34
1793019140 34
1793019145 34
1793019150 34
1793019155 34
1793019160 34
1793019165 34
1793019170 34
1793019175 34
```
</details>

---

