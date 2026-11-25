---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 08:34:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 81-90 cores)</summary>

```
1795613365 81
1795613370 81
1795613375 81
1795613380 81
1795613385 81
1795613390 90
1795613395 90
1795613400 85
1795613405 85
1795613410 85
1795613415 85
1795613420 85
1795613425 85
1795613431 85
1795613436 85
1795613441 85
1795613446 85
1795613451 82
1795613456 82
1795613461 82
```
</details>

---

