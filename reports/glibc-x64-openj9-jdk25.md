---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-07 10:01:24 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (5 unique values: 12-47 cores)</summary>

```
1794063442 14
1794063447 14
1794063452 14
1794063457 16
1794063462 16
1794063467 16
1794063472 16
1794063477 16
1794063482 33
1794063487 33
1794063492 16
1794063497 16
1794063502 16
1794063507 16
1794063512 16
1794063517 16
1794063522 12
1794063527 12
1794063532 12
1794063537 12
```
</details>

---

