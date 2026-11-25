---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795627411 60
1795627416 60
1795627421 60
1795627426 60
1795627431 60
1795627436 60
1795627441 60
1795627446 60
1795627451 60
1795627456 60
1795627461 60
1795627466 60
1795627471 60
1795627476 60
1795627481 64
1795627486 64
1795627491 64
1795627496 64
1795627501 64
1795627506 64
```
</details>

---

