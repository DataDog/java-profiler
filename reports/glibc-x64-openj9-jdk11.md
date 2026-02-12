---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-12 13:12:33 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 65-76 cores)</summary>

```
1770919624 76
1770919629 76
1770919634 76
1770919639 76
1770919644 76
1770919649 74
1770919654 74
1770919659 74
1770919664 74
1770919669 74
1770919674 74
1770919679 70
1770919684 70
1770919689 70
1770919694 65
1770919699 65
1770919704 65
1770919709 65
1770919714 67
1770919719 67
```
</details>

---

