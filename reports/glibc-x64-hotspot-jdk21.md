---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:24:37 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1794244736 32
1794244741 32
1794244746 32
1794244751 32
1794244756 32
1794244761 32
1794244766 32
1794244771 32
1794244776 32
1794244781 32
1794244786 32
1794244791 32
1794244796 32
1794244801 32
1794244806 32
1794244811 32
1794244816 32
1794244821 32
1794244826 15
1794244831 15
```
</details>

---

