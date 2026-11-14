---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-14 13:57:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1794682407 46
1794682412 48
1794682417 48
1794682422 48
1794682427 48
1794682432 48
1794682437 48
1794682442 48
1794682447 48
1794682452 48
1794682457 48
1794682462 48
1794682467 48
1794682472 48
1794682477 48
1794682482 46
1794682487 46
1794682492 41
1794682497 41
1794682502 41
```
</details>

---

