---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 10:36:57 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 9 |
| Allocations | 201 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (6 unique values: 36-56 cores)</summary>

```
1790087384 56
1790087389 56
1790087394 56
1790087399 56
1790087404 55
1790087409 55
1790087414 55
1790087419 55
1790087424 55
1790087429 55
1790087434 55
1790087439 55
1790087444 55
1790087449 53
1790087454 53
1790087459 53
1790087464 53
1790087469 53
1790087474 53
1790087479 50
```
</details>

---

