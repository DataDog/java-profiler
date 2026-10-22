---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 05:55:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1792662619 66
1792662624 66
1792662629 66
1792662634 64
1792662639 64
1792662644 64
1792662649 64
1792662654 64
1792662659 64
1792662664 64
1792662669 64
1792662674 66
1792662679 66
1792662684 66
1792662689 66
1792662694 68
1792662699 68
1792662704 68
1792662709 68
1792662714 68
```
</details>

---

