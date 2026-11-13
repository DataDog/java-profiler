---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 11:34:30 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 76-91 cores)</summary>

```
1794587396 76
1794587401 76
1794587406 76
1794587411 76
1794587416 76
1794587421 76
1794587426 76
1794587431 76
1794587436 76
1794587441 76
1794587446 76
1794587451 76
1794587456 76
1794587461 76
1794587466 76
1794587471 76
1794587476 76
1794587481 76
1794587486 76
1794587491 91
```
</details>

---

