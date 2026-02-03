---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 12:32:23 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770139453 32
1770139458 32
1770139463 32
1770139468 32
1770139473 32
1770139478 32
1770139483 32
1770139488 32
1770139493 32
1770139498 32
1770139503 32
1770139508 32
1770139513 32
1770139518 32
1770139523 32
1770139528 32
1770139533 32
1770139538 32
1770139543 30
1770139548 30
```
</details>

---

