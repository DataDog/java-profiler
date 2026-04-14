---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 06:19:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 75-93 cores)</summary>

```
1776161517 75
1776161522 75
1776161527 75
1776161532 84
1776161537 84
1776161542 84
1776161547 84
1776161552 93
1776161557 93
1776161562 93
1776161567 93
1776161572 93
1776161577 93
1776161582 93
1776161587 93
1776161592 93
1776161597 93
1776161602 93
1776161607 93
1776161612 93
```
</details>

---

