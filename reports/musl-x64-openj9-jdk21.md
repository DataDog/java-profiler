---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795529333 87
1795529338 87
1795529343 87
1795529348 87
1795529353 87
1795529358 87
1795529363 87
1795529368 87
1795529373 87
1795529378 87
1795529383 85
1795529388 85
1795529393 85
1795529398 85
1795529403 85
1795529408 85
1795529413 85
1795529418 85
1795529423 85
1795529428 85
```
</details>

---

