---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-21 09:57:49 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776779603 64
1776779608 64
1776779613 64
1776779618 64
1776779623 64
1776779628 64
1776779633 64
1776779638 64
1776779643 64
1776779648 64
1776779653 64
1776779658 64
1776779663 64
1776779668 64
1776779673 64
1776779678 64
1776779683 64
1776779688 64
1776779693 64
1776779698 64
```
</details>

---

