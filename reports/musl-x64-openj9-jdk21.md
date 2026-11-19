---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 06:28:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 10 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 836 |
| Sample Rate | 13.93/sec |
| Health Score | 871% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 78-89 cores)</summary>

```
1795087357 85
1795087362 85
1795087367 85
1795087372 80
1795087377 80
1795087382 78
1795087387 78
1795087392 78
1795087397 78
1795087402 78
1795087407 78
1795087412 78
1795087417 78
1795087422 78
1795087427 78
1795087432 78
1795087437 87
1795087442 87
1795087447 89
1795087452 89
```
</details>

---

