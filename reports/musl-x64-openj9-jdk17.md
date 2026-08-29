---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-29 05:48:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (5 unique values: 28-36 cores)</summary>

```
1787996596 36
1787996601 36
1787996606 36
1787996611 36
1787996616 36
1787996622 36
1787996627 36
1787996632 36
1787996637 34
1787996642 34
1787996647 32
1787996652 32
1787996657 32
1787996662 32
1787996667 36
1787996672 36
1787996677 36
1787996682 34
1787996687 34
1787996692 32
```
</details>

---

