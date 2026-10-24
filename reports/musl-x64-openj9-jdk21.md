---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:55:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 898 |
| Sample Rate | 14.97/sec |
| Health Score | 936% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 33-72 cores)</summary>

```
1792835477 72
1792835482 72
1792835487 72
1792835492 72
1792835497 72
1792835502 72
1792835507 72
1792835512 37
1792835517 37
1792835522 37
1792835527 37
1792835532 37
1792835537 37
1792835542 39
1792835547 39
1792835552 39
1792835557 39
1792835562 39
1792835567 33
1792835572 33
```
</details>

---

