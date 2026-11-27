---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 06:24:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1795778411 57
1795778416 57
1795778421 57
1795778426 57
1795778431 57
1795778436 55
1795778441 55
1795778446 55
1795778451 55
1795778456 55
1795778461 55
1795778466 55
1795778471 55
1795778476 55
1795778481 55
1795778486 55
1795778491 55
1795778496 55
1795778501 55
1795778506 55
```
</details>

---

