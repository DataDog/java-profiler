---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:32:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 35-62 cores)</summary>

```
1776932895 62
1776932900 62
1776932905 62
1776932910 62
1776932915 62
1776932920 62
1776932925 62
1776932930 62
1776932935 62
1776932940 62
1776932945 62
1776932950 60
1776932955 60
1776932960 60
1776932965 60
1776932970 60
1776932975 60
1776932980 35
1776932985 35
1776932990 35
```
</details>

---

