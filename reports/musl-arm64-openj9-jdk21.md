---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 21:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (2 unique values: 39-43 cores)</summary>

```
1793674443 43
1793674448 43
1793674453 43
1793674458 43
1793674463 43
1793674468 43
1793674473 43
1793674478 43
1793674483 43
1793674488 43
1793674493 43
1793674498 43
1793674503 43
1793674508 43
1793674513 43
1793674518 43
1793674523 43
1793674528 43
1793674533 43
1793674538 43
```
</details>

---

