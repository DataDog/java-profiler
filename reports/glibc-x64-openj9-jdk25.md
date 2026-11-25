---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 3 |

<details>
<summary>CPU Timeline (4 unique values: 55-74 cores)</summary>

```
1795627419 55
1795627424 55
1795627429 74
1795627434 74
1795627439 72
1795627444 72
1795627449 72
1795627454 72
1795627459 72
1795627464 72
1795627469 72
1795627474 72
1795627479 72
1795627484 70
1795627489 70
1795627494 70
1795627499 70
1795627504 70
1795627509 70
1795627514 70
```
</details>

---

