---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 05:15:18 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790327324 43
1790327329 43
1790327334 43
1790327339 43
1790327344 43
1790327349 48
1790327354 48
1790327359 48
1790327364 48
1790327369 48
1790327374 48
1790327379 48
1790327384 48
1790327389 48
1790327394 48
1790327399 48
1790327404 43
1790327409 43
1790327414 43
1790327419 43
```
</details>

---

