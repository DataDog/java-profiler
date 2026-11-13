---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 09:22:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 358 |
| Sample Rate | 5.97/sec |
| Health Score | 373% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1794579389 40
1794579394 40
1794579399 40
1794579404 40
1794579409 39
1794579414 39
1794579419 39
1794579424 39
1794579429 39
1794579434 39
1794579439 39
1794579444 39
1794579449 39
1794579454 39
1794579459 39
1794579464 39
1794579469 39
1794579474 39
1794579479 44
1794579484 44
```
</details>

---

