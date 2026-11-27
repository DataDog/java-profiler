---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 08:39:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 12 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 48-57 cores)</summary>

```
1795786443 48
1795786448 48
1795786453 50
1795786458 50
1795786463 48
1795786468 48
1795786473 48
1795786478 48
1795786483 48
1795786488 48
1795786493 48
1795786498 48
1795786503 48
1795786508 48
1795786513 48
1795786518 48
1795786523 48
1795786528 48
1795786533 48
1795786538 48
```
</details>

---

