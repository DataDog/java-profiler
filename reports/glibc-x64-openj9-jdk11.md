---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:29:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 70-74 cores)</summary>

```
1795627402 70
1795627407 70
1795627412 70
1795627417 70
1795627422 70
1795627427 70
1795627432 70
1795627437 70
1795627442 70
1795627447 70
1795627452 72
1795627457 72
1795627462 72
1795627467 72
1795627472 72
1795627477 72
1795627482 72
1795627487 72
1795627492 72
1795627497 72
```
</details>

---

