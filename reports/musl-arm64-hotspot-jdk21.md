---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 15:47:20 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 12 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795034439 34
1795034444 34
1795034449 34
1795034454 34
1795034459 34
1795034464 34
1795034469 34
1795034474 34
1795034479 34
1795034484 34
1795034489 34
1795034494 34
1795034499 34
1795034504 34
1795034509 34
1795034514 34
1795034519 34
1795034524 29
1795034529 29
1795034534 29
```
</details>

---

