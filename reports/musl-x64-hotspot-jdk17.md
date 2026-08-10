---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 16:31:54 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 36-72 cores)</summary>

```
1786393533 52
1786393538 52
1786393543 52
1786393548 52
1786393553 52
1786393558 52
1786393563 52
1786393568 52
1786393573 52
1786393578 52
1786393583 72
1786393588 72
1786393593 72
1786393598 36
1786393603 36
1786393608 36
1786393613 36
1786393618 36
1786393623 36
1786393628 36
```
</details>

---

