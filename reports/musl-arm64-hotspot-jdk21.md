---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 07:23:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 39-48 cores)</summary>

```
1791371867 39
1791371872 39
1791371877 39
1791371882 39
1791371887 39
1791371892 39
1791371897 40
1791371902 40
1791371907 42
1791371912 42
1791371917 42
1791371922 42
1791371927 42
1791371932 42
1791371937 42
1791371942 42
1791371947 42
1791371952 42
1791371957 42
1791371962 42
```
</details>

---

