---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-22 09:44:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1792676407 27
1792676412 27
1792676417 27
1792676422 27
1792676427 27
1792676432 27
1792676437 27
1792676442 27
1792676447 27
1792676452 29
1792676457 29
1792676462 29
1792676467 29
1792676472 29
1792676477 29
1792676482 29
1792676487 29
1792676492 29
1792676497 29
1792676502 29
```
</details>

---

