---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:07:37 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (4 unique values: 76-83 cores)</summary>

```
1793372553 76
1793372558 76
1793372563 76
1793372568 76
1793372573 76
1793372578 76
1793372583 76
1793372588 76
1793372593 78
1793372598 78
1793372603 78
1793372608 81
1793372613 81
1793372618 83
1793372623 83
1793372628 83
1793372633 83
1793372638 83
1793372643 83
1793372648 81
```
</details>

---

