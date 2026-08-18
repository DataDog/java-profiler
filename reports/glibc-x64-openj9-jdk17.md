---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 10:51:42 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 409 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787064349 96
1787064354 96
1787064359 94
1787064364 94
1787064369 94
1787064374 94
1787064380 94
1787064385 96
1787064390 96
1787064395 96
1787064400 96
1787064405 96
1787064410 96
1787064415 96
1787064420 96
1787064425 96
1787064430 96
1787064435 96
1787064440 96
1787064445 96
```
</details>

---

