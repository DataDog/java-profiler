---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 15:34:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1778095763 81
1778095768 81
1778095773 81
1778095778 76
1778095783 76
1778095788 76
1778095793 76
1778095798 76
1778095803 76
1778095808 76
1778095813 76
1778095818 76
1778095823 76
1778095828 76
1778095833 76
1778095838 76
1778095843 76
1778095848 79
1778095853 79
1778095858 79
```
</details>

---

