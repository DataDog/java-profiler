---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-31 06:39:05 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 10 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1788172403 46
1788172408 47
1788172413 47
1788172418 47
1788172423 47
1788172428 47
1788172433 47
1788172438 47
1788172443 47
1788172448 47
1788172453 47
1788172458 48
1788172463 48
1788172468 48
1788172473 48
1788172478 48
1788172483 48
1788172488 48
1788172493 48
1788172498 48
```
</details>

---

