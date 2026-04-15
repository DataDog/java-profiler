---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-15 15:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 52-67 cores)</summary>

```
1776282591 67
1776282596 67
1776282601 67
1776282606 67
1776282611 59
1776282616 59
1776282621 59
1776282627 59
1776282632 59
1776282637 59
1776282642 59
1776282647 59
1776282652 55
1776282657 55
1776282662 55
1776282667 55
1776282672 55
1776282677 55
1776282682 55
1776282687 55
```
</details>

---

