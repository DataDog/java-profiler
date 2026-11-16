---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-16 11:32:05 EST

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 13-15 cores)</summary>

```
1794846431 15
1794846436 15
1794846441 15
1794846446 15
1794846451 15
1794846456 15
1794846461 15
1794846466 15
1794846471 15
1794846476 15
1794846481 15
1794846486 15
1794846491 15
1794846496 15
1794846501 15
1794846506 15
1794846511 15
1794846516 15
1794846521 15
1794846526 13
```
</details>

---

