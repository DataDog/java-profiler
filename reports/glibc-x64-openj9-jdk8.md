---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-20 09:29:33 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 78-88 cores)</summary>

```
1776691522 88
1776691527 88
1776691532 88
1776691537 83
1776691542 83
1776691547 83
1776691552 83
1776691557 83
1776691562 83
1776691567 83
1776691572 83
1776691577 83
1776691582 83
1776691587 83
1776691592 83
1776691597 81
1776691602 81
1776691607 80
1776691612 80
1776691618 80
```
</details>

---

