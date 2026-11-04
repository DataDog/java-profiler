---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 41-53 cores)</summary>

```
1793801617 48
1793801622 48
1793801627 48
1793801632 48
1793801637 48
1793801642 48
1793801647 48
1793801652 48
1793801657 48
1793801662 53
1793801667 53
1793801672 53
1793801677 53
1793801682 53
1793801687 53
1793801692 53
1793801697 53
1793801702 53
1793801707 53
1793801712 53
```
</details>

---

