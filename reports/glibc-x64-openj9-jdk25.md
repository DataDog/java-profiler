---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:06:33 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1790168551 22
1790168556 22
1790168561 22
1790168566 22
1790168571 22
1790168576 22
1790168581 22
1790168586 22
1790168591 22
1790168596 22
1790168601 22
1790168606 22
1790168612 22
1790168617 20
1790168622 20
1790168627 20
1790168632 20
1790168637 20
1790168642 20
1790168647 22
```
</details>

---

