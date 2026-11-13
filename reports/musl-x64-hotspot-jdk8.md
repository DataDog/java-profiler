---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 06:36:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 178 |
| Sample Rate | 2.97/sec |
| Health Score | 186% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1794569543 91
1794569548 91
1794569553 91
1794569558 91
1794569563 91
1794569568 91
1794569573 91
1794569578 91
1794569583 91
1794569588 91
1794569593 91
1794569598 89
1794569603 89
1794569608 89
1794569613 89
1794569618 89
1794569623 89
1794569628 89
1794569633 89
1794569638 89
```
</details>

---

