---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 00:57:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
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
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
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
1786510507 43
1786510512 43
1786510517 43
1786510522 43
1786510527 43
```
</details>

---

