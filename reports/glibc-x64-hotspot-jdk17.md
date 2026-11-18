---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:31:52 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 11 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 36-66 cores)</summary>

```
1795012025 66
1795012030 66
1795012035 66
1795012040 66
1795012046 66
1795012051 66
1795012056 66
1795012061 66
1795012066 66
1795012071 66
1795012076 66
1795012081 38
1795012086 38
1795012091 38
1795012096 38
1795012101 38
1795012106 38
1795012111 38
1795012116 38
1795012121 38
```
</details>

---

