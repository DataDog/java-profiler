---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-13 05:26:06 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 29-34 cores)</summary>

```
1773393615 32
1773393620 32
1773393625 32
1773393630 32
1773393635 32
1773393640 32
1773393645 32
1773393650 32
1773393655 32
1773393660 32
1773393665 32
1773393670 32
1773393675 32
1773393680 34
1773393685 34
1773393690 34
1773393695 34
1773393700 34
1773393705 29
1773393710 29
```
</details>

---

