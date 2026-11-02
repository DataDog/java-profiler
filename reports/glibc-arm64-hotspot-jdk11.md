---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 06:22:19 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793618334 48
1793618339 48
1793618344 48
1793618349 48
1793618354 48
1793618359 48
1793618364 48
1793618369 48
1793618374 48
1793618379 48
1793618384 48
1793618389 48
1793618394 48
1793618399 48
1793618404 48
1793618409 48
1793618415 48
1793618420 48
1793618425 48
1793618430 48
```
</details>

---

