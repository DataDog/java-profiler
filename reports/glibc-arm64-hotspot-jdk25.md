---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 07:26:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 9 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1794572502 43
1794572508 43
1794572513 43
1794572518 43
1794572523 43
1794572528 38
1794572533 38
1794572538 38
1794572543 38
1794572548 38
1794572553 38
1794572558 38
1794572563 38
1794572568 38
1794572573 38
1794572578 38
1794572583 38
1794572588 38
1794572593 38
1794572598 43
```
</details>

---

