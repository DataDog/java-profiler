---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-05 08:26:03 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 792 |
| Sample Rate | 13.20/sec |
| Health Score | 825% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 56-74 cores)</summary>

```
1785932413 74
1785932418 74
1785932423 74
1785932428 74
1785932433 72
1785932438 72
1785932443 72
1785932448 72
1785932453 72
1785932458 74
1785932463 74
1785932468 66
1785932473 66
1785932478 66
1785932483 66
1785932488 66
1785932493 66
1785932498 66
1785932503 66
1785932508 66
```
</details>

---

