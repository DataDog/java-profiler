---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 20:29:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 32-51 cores)</summary>

```
1795397136 51
1795397141 51
1795397146 51
1795397151 51
1795397156 51
1795397161 51
1795397166 51
1795397171 51
1795397176 51
1795397181 51
1795397186 51
1795397191 51
1795397196 51
1795397201 51
1795397206 34
1795397211 34
1795397216 34
1795397221 34
1795397226 34
1795397231 34
```
</details>

---

