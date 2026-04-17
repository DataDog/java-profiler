---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-17 12:00:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 364 |
| Sample Rate | 6.07/sec |
| Health Score | 379% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 45-55 cores)</summary>

```
1776441408 51
1776441413 51
1776441418 51
1776441423 47
1776441428 47
1776441433 47
1776441438 47
1776441443 51
1776441448 51
1776441453 51
1776441458 51
1776441463 55
1776441468 55
1776441473 55
1776441478 55
1776441483 55
1776441488 55
1776441493 55
1776441498 55
1776441503 55
```
</details>

---

