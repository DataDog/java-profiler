---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 8 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795627419 87
1795627424 87
1795627429 87
1795627434 87
1795627439 87
1795627444 87
1795627449 87
1795627454 87
1795627459 87
1795627464 87
1795627469 87
1795627474 87
1795627479 87
1795627484 87
1795627489 87
1795627494 87
1795627499 85
1795627504 85
1795627509 85
1795627514 85
```
</details>

---

