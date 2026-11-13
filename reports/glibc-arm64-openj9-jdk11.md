---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:48:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 11 |
| Allocations | 214 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794595466 46
1794595471 46
1794595476 46
1794595481 46
1794595486 51
1794595491 51
1794595496 51
1794595501 51
1794595506 51
1794595511 51
1794595516 51
1794595521 51
1794595526 51
1794595531 51
1794595536 51
1794595541 51
1794595546 51
1794595551 51
1794595556 51
1794595561 51
```
</details>

---

