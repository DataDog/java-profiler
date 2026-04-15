---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 15:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 26-34 cores)</summary>

```
1776282576 26
1776282581 26
1776282586 26
1776282591 26
1776282596 26
1776282601 30
1776282606 30
1776282611 30
1776282616 30
1776282621 30
1776282626 30
1776282631 34
1776282636 34
1776282641 34
1776282646 34
1776282651 34
1776282656 34
1776282661 34
1776282666 34
1776282671 34
```
</details>

---

