---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 17:04:22 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 66-96 cores)</summary>

```
1795384542 66
1795384547 66
1795384552 66
1795384557 66
1795384562 66
1795384567 66
1795384572 66
1795384577 66
1795384582 66
1795384587 66
1795384592 66
1795384597 94
1795384602 94
1795384607 94
1795384612 94
1795384617 94
1795384622 94
1795384627 94
1795384632 94
1795384637 94
```
</details>

---

