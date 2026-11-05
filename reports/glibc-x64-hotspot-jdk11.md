---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 951 |
| Sample Rate | 15.85/sec |
| Health Score | 991% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (4 unique values: 69-82 cores)</summary>

```
1793895000 69
1793895005 69
1793895010 69
1793895015 69
1793895020 78
1793895025 78
1793895030 80
1793895035 80
1793895040 82
1793895045 82
1793895050 82
1793895055 82
1793895060 82
1793895065 82
1793895070 82
1793895075 82
1793895080 82
1793895085 82
1793895090 82
1793895095 82
```
</details>

---

