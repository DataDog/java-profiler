---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 7 |
| Allocations | 41 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (6 unique values: 13-23 cores)</summary>

```
1789737721 21
1789737726 21
1789737731 21
1789737736 23
1789737741 23
1789737746 17
1789737751 17
1789737756 17
1789737761 17
1789737766 17
1789737771 17
1789737776 16
1789737781 16
1789737786 16
1789737791 16
1789737796 16
1789737801 16
1789737806 13
1789737811 13
1789737816 13
```
</details>

---

