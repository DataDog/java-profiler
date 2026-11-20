---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 11:40:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 86-89 cores)</summary>

```
1795192428 89
1795192433 89
1795192438 89
1795192443 89
1795192448 87
1795192453 87
1795192458 87
1795192463 87
1795192468 87
1795192473 87
1795192478 86
1795192483 86
1795192488 86
1795192493 86
1795192498 86
1795192503 86
1795192508 86
1795192513 86
1795192518 86
1795192523 86
```
</details>

---

