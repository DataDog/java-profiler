---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 842 |
| Sample Rate | 14.03/sec |
| Health Score | 877% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 23-27 cores)</summary>

```
1776352962 25
1776352967 25
1776352972 25
1776352977 25
1776352982 25
1776352987 25
1776352992 27
1776352997 27
1776353002 27
1776353007 27
1776353012 27
1776353017 27
1776353022 23
1776353027 23
1776353032 23
1776353037 23
1776353042 23
1776353047 23
1776353052 23
1776353057 23
```
</details>

---

