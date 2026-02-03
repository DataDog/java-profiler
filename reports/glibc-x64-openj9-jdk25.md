---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 04:27:36 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 12 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770110506 30
1770110511 32
1770110516 32
1770110521 30
1770110526 30
1770110531 30
1770110536 30
1770110541 32
1770110546 32
1770110551 32
1770110556 32
1770110561 32
1770110566 32
1770110571 32
1770110576 32
1770110581 32
1770110586 32
1770110591 32
1770110596 32
1770110601 32
```
</details>

---

