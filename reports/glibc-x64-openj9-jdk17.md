---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-14 01:01:24 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 12-32 cores)</summary>

```
1786683310 20
1786683315 20
1786683320 20
1786683325 20
1786683330 20
1786683335 32
1786683340 32
1786683345 32
1786683350 32
1786683355 32
1786683360 32
1786683365 32
1786683370 32
1786683375 32
1786683380 32
1786683385 32
1786683390 32
1786683395 32
1786683400 32
1786683405 12
```
</details>

---

