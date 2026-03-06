---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-06 04:35:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 11 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 14 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 70-76 cores)</summary>

```
1772789442 70
1772789447 70
1772789452 70
1772789457 70
1772789462 70
1772789467 70
1772789472 70
1772789477 70
1772789482 70
1772789487 70
1772789492 74
1772789497 74
1772789502 74
1772789507 74
1772789512 74
1772789517 76
1772789522 76
1772789527 76
1772789532 76
1772789537 76
```
</details>

---

