---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 09:38:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 46-59 cores)</summary>

```
1793021580 51
1793021585 51
1793021590 51
1793021595 51
1793021600 51
1793021605 51
1793021610 51
1793021615 51
1793021620 51
1793021625 51
1793021630 51
1793021635 51
1793021640 51
1793021645 51
1793021650 51
1793021655 51
1793021660 51
1793021665 51
1793021670 46
1793021675 46
```
</details>

---

