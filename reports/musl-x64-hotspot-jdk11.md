---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-15 08:57:51 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 51-70 cores)</summary>

```
1776257544 70
1776257549 70
1776257554 51
1776257559 51
1776257564 51
1776257569 51
1776257574 51
1776257579 51
1776257584 51
1776257589 51
1776257594 51
1776257599 51
1776257604 51
1776257609 51
1776257614 51
1776257619 51
1776257624 51
1776257629 51
1776257634 51
1776257639 51
```
</details>

---

