---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (3 unique values: 91-94 cores)</summary>

```
1795627405 91
1795627410 91
1795627416 91
1795627421 91
1795627426 91
1795627431 91
1795627436 91
1795627441 91
1795627446 91
1795627451 91
1795627456 91
1795627461 91
1795627466 91
1795627471 91
1795627476 91
1795627481 94
1795627486 94
1795627491 94
1795627496 94
1795627501 92
```
</details>

---

