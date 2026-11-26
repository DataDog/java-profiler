---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 08:21:29 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 46-70 cores)</summary>

```
1795699005 49
1795699010 68
1795699015 68
1795699020 68
1795699025 68
1795699030 68
1795699035 68
1795699040 68
1795699045 68
1795699050 70
1795699055 70
1795699060 46
1795699065 46
1795699070 46
1795699075 46
1795699080 46
1795699085 46
1795699090 46
1795699095 46
1795699100 46
```
</details>

---

