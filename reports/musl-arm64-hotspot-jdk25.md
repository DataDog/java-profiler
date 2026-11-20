---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 12:24:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 47-50 cores)</summary>

```
1795195221 47
1795195226 47
1795195231 47
1795195236 47
1795195241 47
1795195246 47
1795195251 50
1795195257 50
1795195262 50
1795195267 50
1795195272 50
1795195277 50
1795195282 50
1795195287 50
1795195292 50
1795195297 50
1795195302 50
1795195307 50
1795195312 50
1795195317 50
```
</details>

---

