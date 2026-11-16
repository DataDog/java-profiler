---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:32:07 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (4 unique values: 70-82 cores)</summary>

```
1794846408 82
1794846413 80
1794846418 80
1794846423 80
1794846428 80
1794846433 80
1794846438 80
1794846443 80
1794846448 80
1794846453 80
1794846458 80
1794846463 72
1794846468 72
1794846473 72
1794846478 72
1794846483 72
1794846488 72
1794846493 72
1794846498 72
1794846503 72
```
</details>

---

