---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 12:24:42 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
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
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1794590391 38
1794590396 43
1794590401 43
1794590406 43
1794590411 43
1794590416 43
1794590421 43
1794590426 43
1794590431 43
1794590436 43
1794590441 43
1794590446 43
1794590451 43
1794590456 43
1794590461 43
1794590466 43
1794590471 43
1794590476 43
1794590481 43
1794590486 43
```
</details>

---

