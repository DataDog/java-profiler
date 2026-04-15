---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 45-64 cores)</summary>

```
1776282573 62
1776282578 62
1776282583 62
1776282588 62
1776282593 64
1776282598 64
1776282603 59
1776282608 59
1776282613 59
1776282618 59
1776282623 59
1776282628 59
1776282633 50
1776282638 50
1776282643 50
1776282648 50
1776282653 50
1776282658 45
1776282663 45
1776282668 45
```
</details>

---

