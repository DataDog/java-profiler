---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 10:43:22 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1790692697 31
1790692702 31
1790692707 31
1790692712 31
1790692717 31
1790692722 31
1790692727 31
1790692732 31
1790692737 31
1790692742 31
1790692747 31
1790692752 31
1790692757 31
1790692762 31
1790692767 31
1790692772 31
1790692777 31
1790692782 31
1790692787 31
1790692792 31
```
</details>

---

