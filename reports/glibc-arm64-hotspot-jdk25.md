---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 07:23:17 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787224741 64
1787224746 64
1787224751 64
1787224756 64
1787224761 64
1787224766 64
1787224771 64
1787224776 64
1787224781 64
1787224786 64
1787224791 64
1787224796 64
1787224801 64
1787224806 64
1787224811 64
1787224816 64
1787224822 64
1787224827 64
1787224832 64
1787224837 64
```
</details>

---

