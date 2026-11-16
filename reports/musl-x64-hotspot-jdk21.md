---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 00:05:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 58-64 cores)</summary>

```
1794805235 58
1794805240 58
1794805245 58
1794805251 62
1794805256 62
1794805261 62
1794805266 62
1794805271 64
1794805276 64
1794805281 64
1794805286 64
1794805291 64
1794805296 64
1794805301 64
1794805306 64
1794805311 64
1794805316 64
1794805321 64
1794805326 64
1794805331 64
```
</details>

---

