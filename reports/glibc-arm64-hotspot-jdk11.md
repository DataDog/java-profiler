---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 15:54:55 EDT

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
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 35 |
| Sample Rate | 0.58/sec |
| Health Score | 36% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776282608 64
1776282613 64
1776282618 64
1776282623 64
1776282628 64
1776282633 64
1776282638 64
1776282643 64
1776282648 64
1776282653 64
1776282658 64
1776282663 64
1776282668 64
1776282673 64
1776282678 64
1776282683 64
1776282688 64
1776282693 64
1776282698 64
1776282703 64
```
</details>

---

