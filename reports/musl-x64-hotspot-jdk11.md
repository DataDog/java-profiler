---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 62-66 cores)</summary>

```
1776282589 63
1776282594 63
1776282599 63
1776282604 63
1776282609 63
1776282614 63
1776282619 63
1776282624 63
1776282629 62
1776282634 62
1776282639 62
1776282644 62
1776282649 62
1776282654 62
1776282659 62
1776282664 62
1776282669 62
1776282674 62
1776282679 62
1776282684 62
```
</details>

---

