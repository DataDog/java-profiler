---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:34:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 13 |
| Allocations | 164 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1789716442 44
1789716447 44
1789716452 44
1789716457 44
1789716462 44
1789716467 44
1789716472 44
1789716477 44
1789716482 44
1789716487 44
1789716492 44
1789716498 44
1789716503 44
1789716508 44
1789716513 44
1789716518 44
1789716523 44
1789716528 44
1789716533 44
1789716538 44
```
</details>

---

