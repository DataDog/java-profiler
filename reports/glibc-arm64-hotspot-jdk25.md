---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 19:41:07 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1792712272 48
1792712277 48
1792712282 48
1792712287 48
1792712292 48
1792712297 48
1792712302 48
1792712307 48
1792712312 28
1792712317 28
1792712322 28
1792712327 28
1792712332 28
1792712337 28
1792712342 28
1792712347 28
1792712352 28
1792712357 28
1792712362 28
1792712367 28
```
</details>

---

