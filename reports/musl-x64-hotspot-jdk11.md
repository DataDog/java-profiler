---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-21 06:25:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 70-80 cores)</summary>

```
1776766606 76
1776766611 76
1776766616 76
1776766621 76
1776766626 76
1776766631 76
1776766636 76
1776766641 76
1776766646 76
1776766651 76
1776766656 76
1776766661 80
1776766666 80
1776766671 80
1776766676 80
1776766681 80
1776766686 80
1776766691 80
1776766696 80
1776766701 80
```
</details>

---

