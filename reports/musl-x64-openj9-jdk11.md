---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:55:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1047 |
| Sample Rate | 17.45/sec |
| Health Score | 1091% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 44-46 cores)</summary>

```
1793634636 46
1793634641 46
1793634646 46
1793634651 46
1793634656 46
1793634661 46
1793634666 46
1793634671 46
1793634676 46
1793634681 46
1793634686 46
1793634691 46
1793634696 46
1793634701 44
1793634706 44
1793634711 44
1793634716 44
1793634721 44
1793634726 44
1793634731 44
```
</details>

---

