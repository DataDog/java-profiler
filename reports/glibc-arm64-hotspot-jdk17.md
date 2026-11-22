---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 17:04:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795384577 64
1795384582 64
1795384587 64
1795384592 64
1795384597 64
1795384602 64
1795384607 64
1795384612 64
1795384617 64
1795384622 64
1795384627 64
1795384632 64
1795384637 64
1795384642 64
1795384647 64
1795384652 64
1795384657 64
1795384662 64
1795384667 64
1795384672 64
```
</details>

---

