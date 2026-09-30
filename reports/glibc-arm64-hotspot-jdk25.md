---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 15 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1790785558 19
1790785563 19
1790785568 19
1790785573 19
1790785578 19
1790785583 19
1790785588 19
1790785593 19
1790785598 19
1790785603 19
1790785608 19
1790785613 19
1790785618 19
1790785623 19
1790785628 19
1790785633 19
1790785638 19
1790785643 19
1790785648 19
1790785653 24
```
</details>

---

