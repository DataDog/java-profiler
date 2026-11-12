---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:03:28 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 13 |
| Allocations | 179 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794488356 48
1794488361 48
1794488366 48
1794488371 48
1794488376 48
1794488381 48
1794488386 48
1794488391 48
1794488396 48
1794488401 48
1794488406 48
1794488411 48
1794488416 48
1794488421 48
1794488426 43
1794488431 43
1794488436 38
1794488441 38
1794488446 38
1794488451 38
```
</details>

---

