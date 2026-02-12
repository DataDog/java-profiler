---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-12 08:15:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 13 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 88-96 cores)</summary>

```
1770901515 96
1770901520 96
1770901525 96
1770901530 96
1770901535 96
1770901540 96
1770901545 96
1770901550 91
1770901555 91
1770901560 91
1770901565 91
1770901570 91
1770901575 91
1770901580 91
1770901585 91
1770901590 88
1770901595 88
1770901600 88
1770901605 88
1770901610 88
```
</details>

---

