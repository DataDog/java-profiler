---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 05:58:33 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793789573 48
1793789578 48
1793789583 48
1793789588 48
1793789593 48
1793789598 48
1793789603 48
1793789608 48
1793789613 48
1793789618 48
1793789623 48
1793789628 48
1793789633 48
1793789638 48
1793789643 48
1793789648 48
1793789653 36
1793789658 36
1793789663 36
1793789668 36
```
</details>

---

