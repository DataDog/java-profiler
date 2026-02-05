---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-05 15:03:47 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 10 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1770321507 81
1770321512 81
1770321517 81
1770321522 75
1770321527 75
1770321532 75
1770321537 75
1770321542 78
1770321547 78
1770321552 78
1770321557 78
1770321562 72
1770321567 72
1770321572 72
1770321577 72
1770321582 72
1770321587 72
1770321593 72
1770321598 72
1770321603 72
```
</details>

---

