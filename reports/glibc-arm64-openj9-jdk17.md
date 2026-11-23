---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:55:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795434638 64
1795434643 64
1795434648 64
1795434653 64
1795434658 64
1795434663 64
1795434668 64
1795434673 64
1795434678 64
1795434683 64
1795434688 64
1795434693 64
1795434698 64
1795434703 64
1795434708 64
1795434713 64
1795434718 64
1795434723 64
1795434728 64
1795434733 64
```
</details>

---

