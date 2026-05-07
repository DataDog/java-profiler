---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:58:42 EDT

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 7 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778165573 59
1778165578 59
1778165583 59
1778165588 59
1778165593 59
1778165598 59
1778165604 59
1778165609 59
1778165614 64
1778165619 64
1778165624 64
1778165629 64
1778165634 64
1778165639 64
1778165644 64
1778165649 64
1778165654 64
1778165659 64
1778165664 64
1778165669 64
```
</details>

---

