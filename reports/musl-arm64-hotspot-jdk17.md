---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 06:24:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795778434 47
1795778439 47
1795778444 47
1795778449 47
1795778454 47
1795778459 47
1795778464 47
1795778469 47
1795778474 64
1795778479 64
1795778484 64
1795778489 64
1795778494 64
1795778499 64
1795778504 64
1795778509 64
1795778514 64
1795778519 64
1795778524 64
1795778529 64
```
</details>

---

