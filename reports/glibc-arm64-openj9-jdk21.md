---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-03 07:41:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 9 |
| Allocations | 189 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 44-47 cores)</summary>

```
1793709467 45
1793709472 45
1793709477 45
1793709482 45
1793709487 44
1793709492 44
1793709497 44
1793709502 44
1793709507 44
1793709512 44
1793709517 44
1793709522 44
1793709527 44
1793709532 44
1793709537 45
1793709542 45
1793709547 45
1793709552 45
1793709557 47
1793709562 47
```
</details>

---

