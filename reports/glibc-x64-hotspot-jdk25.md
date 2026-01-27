---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 11:39:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 19.37/sec |
| Health Score | 1211% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 26.70/sec |
| Health Score | 1669% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1769531578 31
1769531583 31
1769531588 31
1769531593 31
1769531598 33
1769531603 33
1769531608 33
1769531613 33
1769531618 31
1769531623 31
1769531628 31
1769531633 31
1769531638 31
1769531643 31
1769531648 33
1769531653 33
1769531658 33
1769531663 33
1769531668 33
1769531673 33
```
</details>

---

