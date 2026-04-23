---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 13:55:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1776966629 64
1776966634 64
1776966639 64
1776966644 64
1776966649 64
1776966654 64
1776966659 64
1776966664 64
1776966669 64
1776966674 64
1776966679 64
1776966684 64
1776966689 64
1776966694 64
1776966700 64
1776966705 64
1776966710 64
1776966715 64
1776966720 64
1776966725 64
```
</details>

---

