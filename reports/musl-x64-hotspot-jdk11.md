---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (6 unique values: 59-87 cores)</summary>

```
1794567548 59
1794567553 59
1794567558 75
1794567563 75
1794567568 75
1794567573 75
1794567578 75
1794567583 75
1794567588 75
1794567593 77
1794567598 77
1794567603 79
1794567608 79
1794567613 79
1794567618 87
1794567623 87
1794567628 87
1794567633 87
1794567638 66
1794567643 66
```
</details>

---

