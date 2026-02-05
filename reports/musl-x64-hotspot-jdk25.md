---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 11 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 13 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (4 unique values: 84-96 cores)</summary>

```
1770321461 84
1770321466 84
1770321471 84
1770321476 84
1770321481 84
1770321486 88
1770321491 88
1770321496 88
1770321501 96
1770321506 96
1770321511 96
1770321516 96
1770321521 96
1770321526 96
1770321531 96
1770321536 96
1770321541 96
1770321546 96
1770321551 96
1770321556 96
```
</details>

---

