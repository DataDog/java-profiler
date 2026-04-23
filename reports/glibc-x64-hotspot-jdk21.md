---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-23 04:27:28 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 6 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 6-48 cores)</summary>

```
1776932290 11
1776932295 11
1776932300 11
1776932305 11
1776932310 11
1776932315 11
1776932320 11
1776932325 11
1776932330 11
1776932335 11
1776932340 11
1776932345 48
1776932350 48
1776932355 48
1776932360 48
1776932365 11
1776932370 11
1776932375 6
1776932380 6
1776932385 6
```
</details>

---

