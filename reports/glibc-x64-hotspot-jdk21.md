---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 10:31:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 25-28 cores)</summary>

```
1776694888 28
1776694893 28
1776694898 26
1776694903 26
1776694908 26
1776694913 26
1776694918 25
1776694923 25
1776694928 25
1776694933 25
1776694938 25
1776694943 25
1776694948 26
1776694953 26
1776694958 26
1776694963 26
1776694968 26
1776694973 26
1776694978 26
1776694983 26
```
</details>

---

