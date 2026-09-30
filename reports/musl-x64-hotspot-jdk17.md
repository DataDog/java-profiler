---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 12:30:30 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790785543 48
1790785548 48
1790785553 48
1790785558 48
1790785563 48
1790785568 48
1790785573 48
1790785578 48
1790785583 48
1790785588 48
1790785593 48
1790785598 48
1790785603 48
1790785608 48
1790785613 48
1790785618 48
1790785623 48
1790785628 48
1790785633 48
1790785638 46
```
</details>

---

