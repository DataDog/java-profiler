---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-14 06:19:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1776161493 45
1776161498 45
1776161503 45
1776161508 45
1776161513 45
1776161518 45
1776161523 54
1776161528 54
1776161533 54
1776161538 54
1776161543 54
1776161548 54
1776161553 54
1776161558 54
1776161563 54
1776161568 54
1776161573 64
1776161578 64
1776161583 64
1776161588 64
```
</details>

---

