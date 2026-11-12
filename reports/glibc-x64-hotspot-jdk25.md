---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 08:02:20 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 8 |
| Allocations | 426 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1794488221 29
1794488226 29
1794488231 29
1794488236 29
1794488241 29
1794488246 29
1794488251 29
1794488256 29
1794488261 29
1794488266 32
1794488271 32
1794488276 32
1794488281 32
1794488286 32
1794488291 32
1794488296 32
1794488301 32
1794488306 32
1794488311 32
1794488316 32
```
</details>

---

