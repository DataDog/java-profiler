---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-22 00:56:48 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1790052811 40
1790052816 40
1790052821 40
1790052826 40
1790052831 40
1790052836 40
1790052841 40
1790052846 40
1790052851 40
1790052856 40
1790052861 40
1790052866 40
1790052871 40
1790052876 40
1790052881 40
1790052886 40
1790052891 40
1790052896 40
1790052901 40
1790052906 40
```
</details>

---

