---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 12:49:13 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 990 |
| Sample Rate | 16.50/sec |
| Health Score | 1031% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1776271500 45
1776271505 45
1776271510 45
1776271515 45
1776271520 40
1776271525 40
1776271530 40
1776271535 40
1776271540 42
1776271545 42
1776271550 42
1776271555 42
1776271560 42
1776271565 42
1776271570 42
1776271575 42
1776271580 42
1776271585 42
1776271590 42
1776271595 42
```
</details>

---

