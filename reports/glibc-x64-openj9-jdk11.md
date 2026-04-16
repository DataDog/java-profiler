---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 08:32:29 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 993 |
| Sample Rate | 16.55/sec |
| Health Score | 1034% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1776342381 42
1776342386 42
1776342391 42
1776342396 42
1776342401 42
1776342406 42
1776342411 44
1776342416 44
1776342421 44
1776342426 44
1776342431 44
1776342436 44
1776342441 44
1776342446 44
1776342451 44
1776342456 44
1776342461 44
1776342466 44
1776342471 44
1776342476 44
```
</details>

---

