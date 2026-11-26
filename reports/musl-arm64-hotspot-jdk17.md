---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:53:12 EST

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
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 14 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795704445 47
1795704450 47
1795704455 47
1795704460 47
1795704465 47
1795704470 47
1795704475 47
1795704480 47
1795704485 47
1795704490 47
1795704495 47
1795704500 47
1795704505 47
1795704510 47
1795704515 42
1795704520 42
1795704525 42
1795704530 42
1795704535 42
1795704540 42
```
</details>

---

