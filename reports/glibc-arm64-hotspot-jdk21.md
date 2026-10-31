---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 21:17:47 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793409240 40
1793409245 40
1793409250 40
1793409255 40
1793409260 40
1793409265 40
1793409270 40
1793409275 40
1793409280 40
1793409285 40
1793409290 40
1793409295 40
1793409300 40
1793409305 40
1793409310 40
1793409315 40
1793409320 40
1793409325 40
1793409330 40
1793409335 40
```
</details>

---

