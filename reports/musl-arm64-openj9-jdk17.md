---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 10:41:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (1 unique values: 9-9 cores)</summary>

```
1793633770 9
1793633775 9
1793633780 9
1793633785 9
1793633790 9
1793633795 9
1793633800 9
1793633805 9
1793633810 9
1793633815 9
1793633820 9
1793633825 9
1793633830 9
1793633835 9
1793633840 9
1793633845 9
1793633850 9
1793633855 9
1793633860 9
1793633865 9
```
</details>

---

