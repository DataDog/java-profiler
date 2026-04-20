---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 09:29:31 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 20-25 cores)</summary>

```
1776691504 25
1776691509 25
1776691514 25
1776691519 25
1776691524 25
1776691529 25
1776691534 25
1776691539 25
1776691544 25
1776691549 25
1776691554 25
1776691559 25
1776691564 20
1776691569 20
1776691575 20
1776691580 20
1776691585 20
1776691590 20
1776691595 20
1776691600 20
```
</details>

---

