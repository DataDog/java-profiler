---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-14 13:34:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (6 unique values: 60-78 cores)</summary>

```
1776187716 64
1776187721 60
1776187726 60
1776187731 63
1776187736 63
1776187741 63
1776187746 63
1776187751 63
1776187756 70
1776187761 70
1776187766 74
1776187771 74
1776187776 74
1776187781 78
1776187786 78
1776187791 78
1776187796 78
1776187801 78
1776187806 78
1776187811 78
```
</details>

---

