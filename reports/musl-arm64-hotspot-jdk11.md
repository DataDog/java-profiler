---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 00:57:49 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1786510407 38
1786510412 38
1786510417 38
1786510422 38
1786510427 38
1786510432 38
1786510437 38
1786510442 38
1786510447 38
1786510452 38
1786510457 43
1786510462 43
1786510467 43
1786510472 43
1786510477 43
1786510482 43
1786510487 43
1786510492 43
1786510497 43
1786510502 43
```
</details>

---

