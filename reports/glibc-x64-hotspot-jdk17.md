---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-17 06:07:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (7 unique values: 41-65 cores)</summary>

```
1776420227 41
1776420232 41
1776420237 41
1776420242 41
1776420247 41
1776420252 41
1776420257 41
1776420262 41
1776420267 45
1776420272 45
1776420277 45
1776420282 45
1776420287 45
1776420292 42
1776420297 42
1776420302 54
1776420307 54
1776420312 54
1776420317 54
1776420322 57
```
</details>

---

