---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1776440572 77
1776440577 77
1776440582 77
1776440587 77
1776440592 77
1776440597 79
1776440602 79
1776440607 74
1776440612 74
1776440617 74
1776440622 74
1776440627 69
1776440632 69
1776440637 69
1776440642 69
1776440647 69
1776440652 69
1776440657 69
1776440662 69
1776440668 69
```
</details>

---

