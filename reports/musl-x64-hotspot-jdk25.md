---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-09 05:44:49 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 21-29 cores)</summary>

```
1791538751 22
1791538756 22
1791538761 22
1791538767 22
1791538772 24
1791538777 24
1791538782 24
1791538787 24
1791538792 21
1791538797 21
1791538802 21
1791538807 21
1791538812 21
1791538817 21
1791538822 21
1791538827 21
1791538832 21
1791538837 21
1791538842 21
1791538847 21
```
</details>

---

