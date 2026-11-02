---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 06:22:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 545 |

<details>
<summary>CPU Timeline (3 unique values: 53-72 cores)</summary>

```
1793618301 53
1793618306 53
1793618311 53
1793618316 72
1793618321 72
1793618326 72
1793618331 70
1793618336 70
1793618341 70
1793618346 70
1793618351 70
1793618356 70
1793618361 70
1793618366 70
1793618371 70
1793618376 70
1793618381 70
1793618386 70
1793618391 70
1793618396 70
```
</details>

---

