---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 09:32:23 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 21 |
| Sample Rate | 0.35/sec |
| Health Score | 22% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1786368429 37
1786368434 37
1786368439 37
1786368444 37
1786368449 37
1786368454 37
1786368459 37
1786368464 43
1786368469 43
1786368474 43
1786368479 43
1786368484 43
1786368489 43
1786368494 43
1786368499 43
1786368504 43
1786368509 43
1786368514 43
1786368519 43
1786368524 48
```
</details>

---

