---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 06:28:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795087382 64
1795087387 64
1795087392 64
1795087397 64
1795087402 64
1795087407 64
1795087412 64
1795087417 64
1795087422 64
1795087427 64
1795087432 64
1795087437 64
1795087442 64
1795087447 64
1795087452 64
1795087457 64
1795087462 64
1795087467 50
1795087472 50
1795087477 50
```
</details>

---

