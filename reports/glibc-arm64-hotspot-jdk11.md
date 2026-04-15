---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:14:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776265613 64
1776265618 64
1776265623 64
1776265628 64
1776265633 64
1776265638 64
1776265643 64
1776265648 64
1776265653 64
1776265658 64
1776265663 64
1776265668 64
1776265673 64
1776265678 64
1776265683 64
1776265688 64
1776265693 64
1776265698 64
1776265703 64
1776265708 64
```
</details>

---

