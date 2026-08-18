---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 15:26:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 424 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787080960 96
1787080965 96
1787080970 96
1787080975 96
1787080980 94
1787080985 94
1787080990 94
1787080995 94
1787081000 94
1787081005 94
1787081010 94
1787081015 94
1787081020 94
1787081025 94
1787081030 94
1787081035 94
1787081040 94
1787081045 92
1787081050 92
1787081055 92
```
</details>

---

