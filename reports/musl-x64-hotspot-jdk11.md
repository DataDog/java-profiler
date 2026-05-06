---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:08:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (7 unique values: 57-90 cores)</summary>

```
1778090390 59
1778090395 59
1778090400 59
1778090405 59
1778090410 59
1778090415 57
1778090420 57
1778090425 69
1778090430 69
1778090435 69
1778090440 69
1778090445 69
1778090450 69
1778090455 69
1778090460 71
1778090465 71
1778090470 71
1778090475 90
1778090480 90
1778090485 87
```
</details>

---

