---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 159 |
| Sample Rate | 2.65/sec |
| Health Score | 166% |
| Threads | 13 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 30-51 cores)</summary>

```
1786119593 30
1786119598 51
1786119603 51
1786119608 51
1786119613 51
1786119618 51
1786119623 51
1786119628 51
1786119633 51
1786119639 51
1786119644 51
1786119649 51
1786119654 51
1786119659 51
1786119664 51
1786119669 51
1786119674 51
1786119679 51
1786119684 51
1786119689 51
```
</details>

---

