---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 06:22:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (4 unique values: 16-25 cores)</summary>

```
1776680297 16
1776680302 16
1776680307 16
1776680312 16
1776680317 20
1776680322 20
1776680327 19
1776680332 19
1776680337 19
1776680342 19
1776680347 20
1776680352 20
1776680357 16
1776680362 16
1776680367 16
1776680372 16
1776680377 16
1776680382 16
1776680387 16
1776680392 16
```
</details>

---

