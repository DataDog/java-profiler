---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 08:27:58 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1776687628 49
1776687633 49
1776687638 49
1776687643 49
1776687648 59
1776687653 59
1776687658 59
1776687663 59
1776687668 64
1776687673 64
1776687678 64
1776687683 64
1776687688 64
1776687693 63
1776687698 63
1776687703 63
1776687708 63
1776687713 63
1776687718 63
1776687723 63
```
</details>

---

