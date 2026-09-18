---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:37:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1789716798 44
1789716803 44
1789716808 44
1789716813 44
1789716818 44
1789716823 44
1789716828 44
1789716833 44
1789716838 44
1789716843 44
1789716848 44
1789716853 44
1789716858 44
1789716863 64
1789716868 64
1789716873 64
1789716878 64
1789716883 64
1789716888 64
1789716893 64
```
</details>

---

