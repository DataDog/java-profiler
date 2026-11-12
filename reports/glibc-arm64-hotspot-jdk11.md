---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:02:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 10 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 13 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1794488275 44
1794488280 44
1794488285 44
1794488290 44
1794488295 48
1794488300 48
1794488305 48
1794488310 48
1794488315 48
1794488320 48
1794488325 48
1794488330 48
1794488335 48
1794488340 48
1794488345 48
1794488351 48
1794488356 48
1794488361 48
1794488366 48
1794488371 48
```
</details>

---

