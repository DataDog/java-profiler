---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:44:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 823 |
| Sample Rate | 13.72/sec |
| Health Score | 857% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 60-69 cores)</summary>

```
1789731576 61
1789731581 61
1789731586 61
1789731591 61
1789731596 61
1789731601 69
1789731606 69
1789731611 69
1789731616 69
1789731621 69
1789731626 69
1789731631 69
1789731636 69
1789731641 69
1789731646 69
1789731651 69
1789731656 69
1789731661 69
1789731666 69
1789731671 68
```
</details>

---

