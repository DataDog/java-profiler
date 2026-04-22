---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-22 03:53:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1776844198 23
1776844203 23
1776844208 23
1776844213 23
1776844218 23
1776844223 23
1776844228 23
1776844233 23
1776844238 23
1776844243 23
1776844248 23
1776844253 23
1776844258 28
1776844263 28
1776844268 28
1776844273 28
1776844278 28
1776844283 28
1776844288 28
1776844293 28
```
</details>

---

