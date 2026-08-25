---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-25 08:39:36 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787661354 96
1787661359 96
1787661364 96
1787661369 96
1787661374 96
1787661380 96
1787661385 96
1787661390 96
1787661395 96
1787661400 96
1787661405 96
1787661410 96
1787661415 96
1787661420 96
1787661425 96
1787661430 94
1787661435 94
1787661440 94
1787661445 94
1787661450 94
```
</details>

---

