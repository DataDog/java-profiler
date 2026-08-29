---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-29 05:48:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (5 unique values: 28-36 cores)</summary>

```
1787996647 34
1787996652 32
1787996657 32
1787996662 34
1787996667 34
1787996672 34
1787996677 34
1787996682 36
1787996687 36
1787996692 36
1787996697 36
1787996702 32
1787996707 32
1787996712 32
1787996717 32
1787996722 32
1787996727 32
1787996732 32
1787996737 34
1787996742 34
```
</details>

---

