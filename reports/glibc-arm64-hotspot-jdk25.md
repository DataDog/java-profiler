---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:31:39 EST

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 561 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1795397266 48
1795397271 48
1795397276 48
1795397281 48
1795397286 48
1795397291 48
1795397296 48
1795397301 48
1795397306 48
1795397311 48
1795397316 48
1795397321 48
1795397326 48
1795397331 48
1795397336 48
1795397341 48
1795397346 48
1795397351 48
1795397356 48
1795397361 48
```
</details>

---

