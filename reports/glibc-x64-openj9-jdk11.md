---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-13 11:55:57 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1776095492 85
1776095497 85
1776095502 85
1776095507 85
1776095512 85
1776095517 85
1776095522 85
1776095527 85
1776095532 85
1776095537 85
1776095543 85
1776095548 85
1776095553 85
1776095558 85
1776095563 85
1776095568 85
1776095573 85
1776095578 85
1776095583 83
1776095588 83
```
</details>

---

