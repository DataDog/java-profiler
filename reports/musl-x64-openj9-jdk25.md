---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 11:32:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1012 |
| Sample Rate | 16.87/sec |
| Health Score | 1054% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1776352992 32
1776352997 32
1776353002 32
1776353007 32
1776353012 32
1776353017 32
1776353022 32
1776353027 32
1776353032 32
1776353037 32
1776353042 32
1776353047 32
1776353052 32
1776353057 32
1776353062 32
1776353067 32
1776353072 32
1776353077 32
1776353082 32
1776353087 32
```
</details>

---

