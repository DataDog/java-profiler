---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 11:27:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 34-44 cores)</summary>

```
1790090474 44
1790090479 39
1790090484 39
1790090489 39
1790090494 39
1790090499 39
1790090504 39
1790090509 39
1790090514 39
1790090519 39
1790090524 39
1790090529 39
1790090534 39
1790090539 39
1790090544 39
1790090549 34
1790090554 34
1790090559 34
1790090564 34
1790090569 39
```
</details>

---

