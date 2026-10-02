---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-02 05:51:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 10 |
| Allocations | 557 |

<details>
<summary>CPU Timeline (2 unique values: 58-96 cores)</summary>

```
1790934393 96
1790934398 96
1790934403 96
1790934408 96
1790934413 96
1790934418 96
1790934423 96
1790934428 96
1790934433 58
1790934438 58
1790934443 58
1790934448 58
1790934453 58
1790934458 58
1790934463 58
1790934468 58
1790934473 58
1790934478 58
1790934483 58
1790934488 58
```
</details>

---

