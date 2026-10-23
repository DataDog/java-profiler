---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 19:01:51 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 13 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792796205 43
1792796210 43
1792796215 43
1792796220 43
1792796225 43
1792796230 43
1792796235 43
1792796240 43
1792796245 43
1792796250 43
1792796255 43
1792796260 43
1792796265 43
1792796270 43
1792796275 48
1792796280 48
1792796285 48
1792796290 48
1792796295 48
1792796300 48
```
</details>

---

