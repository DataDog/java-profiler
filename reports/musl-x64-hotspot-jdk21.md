---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 55-64 cores)</summary>

```
1776282596 56
1776282601 56
1776282606 56
1776282611 56
1776282616 56
1776282621 56
1776282626 60
1776282631 60
1776282636 60
1776282641 60
1776282646 64
1776282651 64
1776282656 64
1776282661 64
1776282666 64
1776282671 64
1776282676 55
1776282681 55
1776282686 59
1776282691 59
```
</details>

---

