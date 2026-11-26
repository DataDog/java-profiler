---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 00:04:43 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795669191 32
1795669196 32
1795669201 32
1795669206 32
1795669211 32
1795669216 32
1795669221 32
1795669226 32
1795669231 32
1795669236 32
1795669241 32
1795669246 32
1795669251 32
1795669256 32
1795669261 32
1795669266 32
1795669271 32
1795669276 32
1795669281 32
1795669286 32
```
</details>

---

