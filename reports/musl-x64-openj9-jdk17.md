---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 67-72 cores)</summary>

```
1794569542 72
1794569547 72
1794569552 72
1794569557 72
1794569562 70
1794569567 70
1794569572 70
1794569577 70
1794569582 70
1794569587 70
1794569592 70
1794569597 70
1794569602 70
1794569607 70
1794569612 70
1794569617 70
1794569622 70
1794569627 70
1794569632 70
1794569637 70
```
</details>

---

