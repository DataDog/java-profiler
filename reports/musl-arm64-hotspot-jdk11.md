---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:37:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795786368 42
1795786373 42
1795786378 42
1795786383 42
1795786388 42
1795786393 42
1795786398 42
1795786403 42
1795786408 42
1795786413 42
1795786418 42
1795786423 42
1795786428 42
1795786433 42
1795786438 42
1795786443 42
1795786448 42
1795786453 42
1795786458 42
1795786463 42
```
</details>

---

