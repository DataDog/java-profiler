---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 15:03:05 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 29-38 cores)</summary>

```
1794340597 38
1794340602 38
1794340607 38
1794340612 38
1794340617 38
1794340622 34
1794340627 34
1794340632 34
1794340637 34
1794340642 34
1794340647 34
1794340652 34
1794340657 34
1794340662 34
1794340667 34
1794340672 34
1794340677 29
1794340682 29
1794340687 29
1794340692 29
```
</details>

---

