---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:55:19 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (5 unique values: 39-44 cores)</summary>

```
1795434635 39
1795434640 40
1795434645 40
1795434650 40
1795434655 40
1795434660 40
1795434665 40
1795434670 40
1795434675 43
1795434680 43
1795434685 43
1795434690 43
1795434695 44
1795434700 44
1795434705 44
1795434710 44
1795434715 44
1795434720 44
1795434725 44
1795434730 44
```
</details>

---

