---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-24 15:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1787600220 86
1787600225 86
1787600230 94
1787600235 94
1787600240 94
1787600245 94
1787600250 94
1787600255 94
1787600260 96
1787600265 96
1787600270 96
1787600275 96
1787600280 96
1787600285 96
1787600290 96
1787600295 96
1787600300 96
1787600305 96
1787600310 96
1787600315 96
```
</details>

---

