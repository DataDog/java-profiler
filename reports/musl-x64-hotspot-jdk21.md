---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 47-52 cores)</summary>

```
1776352977 47
1776352982 47
1776352987 52
1776352992 52
1776352997 47
1776353002 47
1776353007 47
1776353012 47
1776353017 47
1776353022 47
1776353027 50
1776353032 50
1776353037 50
1776353042 50
1776353047 50
1776353052 50
1776353057 50
1776353062 50
1776353067 50
1776353072 50
```
</details>

---

