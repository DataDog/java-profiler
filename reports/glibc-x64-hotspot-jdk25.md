---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 06:24:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 78-87 cores)</summary>

```
1795778431 87
1795778436 87
1795778441 87
1795778446 87
1795778451 87
1795778456 87
1795778461 87
1795778466 87
1795778471 78
1795778476 78
1795778481 78
1795778486 78
1795778491 78
1795778496 78
1795778501 78
1795778506 78
1795778511 78
1795778516 78
1795778521 78
1795778526 78
```
</details>

---

