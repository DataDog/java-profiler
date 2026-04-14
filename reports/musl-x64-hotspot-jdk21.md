---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-14 06:19:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 23-32 cores)</summary>

```
1776161492 32
1776161497 32
1776161502 32
1776161507 32
1776161512 32
1776161517 32
1776161522 32
1776161527 32
1776161532 32
1776161537 27
1776161542 27
1776161547 27
1776161552 27
1776161558 27
1776161563 27
1776161568 27
1776161573 27
1776161578 27
1776161583 27
1776161588 27
```
</details>

---

