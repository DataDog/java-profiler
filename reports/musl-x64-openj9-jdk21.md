---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 19:10:52 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 59-62 cores)</summary>

```
1794355412 62
1794355417 62
1794355422 62
1794355427 62
1794355432 62
1794355437 62
1794355442 59
1794355447 59
1794355452 59
1794355457 59
1794355462 59
1794355467 59
1794355472 59
1794355477 59
1794355482 59
1794355487 59
1794355492 59
1794355497 59
1794355502 59
1794355507 59
```
</details>

---

