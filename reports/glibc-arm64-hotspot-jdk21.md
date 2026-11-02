---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 06:22:19 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1793618316 35
1793618321 35
1793618326 35
1793618331 35
1793618336 35
1793618341 35
1793618346 39
1793618351 39
1793618356 39
1793618361 39
1793618366 39
1793618371 39
1793618376 39
1793618381 39
1793618386 39
1793618391 39
1793618396 39
1793618401 39
1793618406 40
1793618411 40
```
</details>

---

