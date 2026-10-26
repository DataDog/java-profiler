---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 10:05:13 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 11 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1793023285 28
1793023290 28
1793023295 28
1793023300 28
1793023305 28
1793023310 28
1793023315 28
1793023320 28
1793023325 28
1793023330 28
1793023335 28
1793023340 28
1793023345 28
1793023350 28
1793023355 28
1793023360 28
1793023365 28
1793023370 28
1793023375 28
1793023380 48
```
</details>

---

