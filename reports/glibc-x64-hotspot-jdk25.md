---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 13:00:39 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 43-55 cores)</summary>

```
1776272225 55
1776272230 55
1776272235 55
1776272240 51
1776272245 51
1776272250 51
1776272255 51
1776272260 47
1776272265 47
1776272270 43
1776272275 43
1776272280 43
1776272285 43
1776272290 43
1776272295 43
1776272300 43
1776272305 43
1776272310 43
1776272315 43
1776272320 43
```
</details>

---

