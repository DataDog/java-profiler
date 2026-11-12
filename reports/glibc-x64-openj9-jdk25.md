---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:45:29 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 86-93 cores)</summary>

```
1794497511 86
1794497516 86
1794497521 86
1794497526 86
1794497531 86
1794497536 93
1794497541 93
1794497546 93
1794497551 93
1794497556 93
1794497561 93
1794497566 93
1794497571 93
1794497576 93
1794497581 93
1794497586 93
1794497591 93
1794497596 93
1794497601 93
1794497606 93
```
</details>

---

