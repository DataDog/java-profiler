---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 19:52:38 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 13-55 cores)</summary>

```
1793926110 53
1793926115 53
1793926120 53
1793926125 53
1793926130 53
1793926135 55
1793926140 55
1793926145 55
1793926150 55
1793926155 55
1793926160 55
1793926165 55
1793926170 55
1793926175 55
1793926180 55
1793926185 55
1793926190 55
1793926195 55
1793926200 55
1793926205 35
```
</details>

---

