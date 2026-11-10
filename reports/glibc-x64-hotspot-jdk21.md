---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 18:14:38 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 10 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794352238 30
1794352243 30
1794352248 30
1794352253 32
1794352258 32
1794352263 32
1794352268 32
1794352273 32
1794352278 32
1794352283 32
1794352288 32
1794352293 32
1794352298 32
1794352303 32
1794352308 32
1794352313 32
1794352318 32
1794352323 32
1794352328 32
1794352333 32
```
</details>

---

