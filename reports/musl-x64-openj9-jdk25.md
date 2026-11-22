---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 17:04:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 506 |
| Sample Rate | 8.43/sec |
| Health Score | 527% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 31-65 cores)</summary>

```
1795384572 48
1795384577 48
1795384582 48
1795384587 48
1795384592 48
1795384597 57
1795384602 57
1795384607 57
1795384612 57
1795384617 57
1795384622 57
1795384627 65
1795384632 65
1795384637 48
1795384642 48
1795384647 48
1795384652 48
1795384657 48
1795384662 48
1795384667 48
```
</details>

---

