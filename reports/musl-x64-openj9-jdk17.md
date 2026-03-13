---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:26:07 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 32-49 cores)</summary>

```
1773393625 32
1773393630 32
1773393635 32
1773393640 32
1773393645 34
1773393650 34
1773393655 34
1773393660 36
1773393665 36
1773393671 36
1773393676 36
1773393681 36
1773393686 36
1773393691 36
1773393696 36
1773393701 36
1773393706 36
1773393711 36
1773393716 36
1773393721 36
```
</details>

---

