---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:29:46 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 95 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 95-96 cores)</summary>

```
1789712723 96
1789712728 96
1789712733 96
1789712738 96
1789712743 96
1789712748 96
1789712753 96
1789712758 96
1789712763 96
1789712768 96
1789712773 96
1789712778 96
1789712783 96
1789712788 95
1789712793 95
1789712798 95
1789712803 95
1789712808 95
1789712813 95
1789712818 95
```
</details>

---

