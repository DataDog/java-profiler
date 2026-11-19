---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:12:33 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 37-46 cores)</summary>

```
1795097226 37
1795097231 37
1795097236 37
1795097241 37
1795097246 37
1795097251 37
1795097256 37
1795097261 37
1795097266 46
1795097271 46
1795097276 46
1795097281 46
1795097286 46
1795097291 46
1795097296 46
1795097301 46
1795097306 46
1795097311 46
1795097316 46
1795097321 46
```
</details>

---

