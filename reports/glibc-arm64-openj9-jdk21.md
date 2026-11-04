---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1793801637 64
1793801642 30
1793801647 30
1793801652 30
1793801657 30
1793801662 30
1793801667 30
1793801672 30
1793801677 30
1793801682 30
1793801687 30
1793801692 30
1793801697 30
1793801702 30
1793801707 30
1793801712 30
1793801717 30
1793801722 30
1793801727 30
1793801732 30
```
</details>

---

