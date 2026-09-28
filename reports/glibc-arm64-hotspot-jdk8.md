---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-28 09:39:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790602552 32
1790602557 32
1790602562 32
1790602567 32
1790602572 32
1790602577 32
1790602582 32
1790602587 32
1790602592 32
1790602597 32
1790602602 32
1790602607 32
1790602612 32
1790602617 32
1790602622 32
1790602627 32
1790602632 32
1790602637 32
1790602642 32
1790602647 32
```
</details>

---

