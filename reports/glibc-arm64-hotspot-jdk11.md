---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:55:46 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1789667380 48
1789667385 48
1789667390 48
1789667395 48
1789667400 48
1789667405 48
1789667410 48
1789667415 48
1789667420 48
1789667425 48
1789667430 48
1789667435 48
1789667440 48
1789667445 48
1789667450 48
1789667455 48
1789667460 48
1789667465 48
1789667470 48
1789667475 48
```
</details>

---

