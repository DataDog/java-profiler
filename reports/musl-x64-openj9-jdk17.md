---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 11:46:56 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 40-57 cores)</summary>

```
1776440621 55
1776440626 55
1776440631 55
1776440636 55
1776440641 57
1776440646 57
1776440651 57
1776440656 57
1776440661 57
1776440666 57
1776440671 57
1776440676 57
1776440681 57
1776440686 57
1776440691 57
1776440696 57
1776440701 40
1776440706 40
1776440711 40
1776440716 40
```
</details>

---

