---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 08:24:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1787055577 94
1787055582 94
1787055587 84
1787055592 84
1787055597 84
1787055602 84
1787055607 86
1787055612 86
1787055617 86
1787055622 86
1787055627 86
1787055632 86
1787055637 86
1787055642 86
1787055647 86
1787055652 86
1787055657 86
1787055662 86
1787055667 84
1787055672 84
```
</details>

---

