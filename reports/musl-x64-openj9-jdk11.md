---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:06:55 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (3 unique values: 67-76 cores)</summary>

```
1777557785 76
1777557790 76
1777557795 76
1777557800 76
1777557805 76
1777557810 76
1777557815 76
1777557820 72
1777557825 72
1777557830 72
1777557835 72
1777557840 67
1777557845 67
1777557850 67
1777557855 67
1777557860 67
1777557865 67
1777557870 67
1777557875 67
1777557880 67
```
</details>

---

