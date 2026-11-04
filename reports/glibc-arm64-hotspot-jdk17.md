---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 09:07:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 8 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 42-43 cores)</summary>

```
1793800906 43
1793800911 43
1793800916 43
1793800921 43
1793800926 43
1793800931 43
1793800936 43
1793800941 43
1793800946 43
1793800951 43
1793800956 43
1793800961 43
1793800966 43
1793800971 43
1793800976 43
1793800981 43
1793800986 43
1793800991 42
1793800996 42
1793801001 42
```
</details>

---

