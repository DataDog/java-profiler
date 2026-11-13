---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 11:34:30 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 317 |
| Sample Rate | 5.28/sec |
| Health Score | 330% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 56-72 cores)</summary>

```
1794587401 56
1794587406 56
1794587411 56
1794587416 62
1794587421 62
1794587426 62
1794587431 62
1794587436 62
1794587441 62
1794587446 62
1794587451 62
1794587456 62
1794587461 62
1794587466 62
1794587471 62
1794587476 62
1794587481 72
1794587486 72
1794587491 70
1794587496 70
```
</details>

---

