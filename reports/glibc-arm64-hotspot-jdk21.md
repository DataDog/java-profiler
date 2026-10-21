---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-21 06:29:47 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 11 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (5 unique values: 36-46 cores)</summary>

```
1792578374 44
1792578379 44
1792578384 44
1792578389 44
1792578394 44
1792578399 44
1792578404 44
1792578409 44
1792578414 44
1792578419 44
1792578424 44
1792578429 44
1792578434 46
1792578439 46
1792578445 41
1792578450 41
1792578455 41
1792578460 41
1792578465 41
1792578470 41
```
</details>

---

