---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 11 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795434625 44
1795434630 44
1795434635 44
1795434640 49
1795434645 49
1795434650 49
1795434655 49
1795434660 49
1795434665 49
1795434670 44
1795434675 44
1795434680 44
1795434685 44
1795434690 44
1795434695 44
1795434700 44
1795434705 44
1795434710 44
1795434715 44
1795434720 44
```
</details>

---

