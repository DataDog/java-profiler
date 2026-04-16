---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 12:58:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 9 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1776358396 28
1776358401 28
1776358406 28
1776358411 28
1776358416 28
1776358421 28
1776358426 28
1776358431 32
1776358436 32
1776358441 32
1776358446 32
1776358451 32
1776358456 32
1776358461 32
1776358466 32
1776358471 32
1776358476 32
1776358481 32
1776358486 32
1776358491 32
```
</details>

---

