---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 07:58:14 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (3 unique values: 10-13 cores)</summary>

```
1776686030 13
1776686035 13
1776686040 13
1776686045 13
1776686050 13
1776686055 11
1776686060 11
1776686065 11
1776686070 11
1776686075 11
1776686080 11
1776686085 11
1776686090 11
1776686095 11
1776686100 11
1776686105 11
1776686110 11
1776686115 13
1776686120 13
1776686125 13
```
</details>

---

