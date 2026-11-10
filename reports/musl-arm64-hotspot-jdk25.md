---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 10:31:22 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1794324388 43
1794324393 43
1794324398 43
1794324403 43
1794324408 42
1794324413 42
1794324418 42
1794324423 42
1794324428 42
1794324433 42
1794324438 42
1794324443 42
1794324448 42
1794324453 42
1794324458 47
1794324463 47
1794324468 43
1794324473 43
1794324478 43
1794324483 43
```
</details>

---

