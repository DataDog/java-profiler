---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 16:24:54 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793827223 48
1793827228 48
1793827233 48
1793827238 48
1793827243 48
1793827248 48
1793827253 48
1793827258 48
1793827263 48
1793827268 48
1793827273 48
1793827278 48
1793827283 48
1793827288 48
1793827293 48
1793827298 48
1793827303 48
1793827308 48
1793827313 48
1793827318 48
```
</details>

---

