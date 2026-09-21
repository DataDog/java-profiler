---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:40:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 11 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1789997766 49
1789997771 44
1789997776 44
1789997781 44
1789997786 44
1789997791 44
1789997796 44
1789997801 44
1789997806 44
1789997811 44
1789997816 44
1789997821 49
1789997826 49
1789997831 64
1789997836 64
1789997841 64
1789997846 64
1789997851 64
1789997856 64
1789997861 64
```
</details>

---

