---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 43-64 cores)</summary>

```
1776352957 55
1776352962 55
1776352967 60
1776352972 60
1776352977 60
1776352982 60
1776352987 60
1776352992 60
1776352997 60
1776353002 60
1776353007 60
1776353012 60
1776353017 60
1776353022 64
1776353027 64
1776353032 43
1776353037 43
1776353042 43
1776353047 43
1776353052 43
```
</details>

---

