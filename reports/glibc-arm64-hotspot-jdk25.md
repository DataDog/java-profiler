---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 20:23:04 EST

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
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793927867 40
1793927872 40
1793927877 40
1793927882 40
1793927887 40
1793927892 40
1793927897 40
1793927902 40
1793927907 40
1793927912 40
1793927917 40
1793927922 40
1793927927 40
1793927932 40
1793927937 40
1793927942 40
1793927947 40
1793927952 40
1793927957 40
1793927962 40
```
</details>

---

