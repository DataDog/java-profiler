---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-12 11:39:21 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 10 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 985 |
| Sample Rate | 16.42/sec |
| Health Score | 1026% |
| Threads | 12 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 47-55 cores)</summary>

```
1773329606 55
1773329611 55
1773329616 55
1773329621 52
1773329626 52
1773329631 52
1773329636 52
1773329641 52
1773329646 52
1773329651 52
1773329656 52
1773329661 52
1773329666 52
1773329671 52
1773329676 52
1773329681 52
1773329686 52
1773329691 52
1773329696 52
1773329701 52
```
</details>

---

