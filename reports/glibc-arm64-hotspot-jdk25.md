---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 11:59:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1794243196 48
1794243201 48
1794243206 48
1794243211 48
1794243216 48
1794243221 48
1794243226 43
1794243231 43
1794243236 43
1794243241 41
1794243246 41
1794243251 41
1794243256 41
1794243261 41
1794243266 41
1794243271 41
1794243276 41
1794243281 41
1794243286 41
1794243291 41
```
</details>

---

