---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 04:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (6 unique values: 54-65 cores)</summary>

```
1776932446 56
1776932451 56
1776932456 56
1776932461 54
1776932466 54
1776932471 56
1776932476 56
1776932481 56
1776932486 56
1776932491 56
1776932496 56
1776932501 56
1776932506 58
1776932511 58
1776932516 58
1776932521 60
1776932526 60
1776932531 60
1776932536 60
1776932541 60
```
</details>

---

