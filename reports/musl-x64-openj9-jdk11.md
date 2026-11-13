---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794569542 64
1794569547 64
1794569552 64
1794569557 64
1794569562 64
1794569567 64
1794569572 64
1794569577 64
1794569582 64
1794569587 64
1794569592 64
1794569597 64
1794569602 64
1794569607 64
1794569612 64
1794569617 64
1794569622 64
1794569627 64
1794569632 64
1794569637 64
```
</details>

---

