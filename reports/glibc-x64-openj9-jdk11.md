---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:55:17 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1792835482 70
1792835487 70
1792835492 70
1792835497 70
1792835502 70
1792835507 70
1792835512 72
1792835517 72
1792835522 72
1792835527 72
1792835532 72
1792835537 72
1792835542 72
1792835547 72
1792835552 72
1792835557 72
1792835562 72
1792835567 72
1792835572 72
1792835577 72
```
</details>

---

