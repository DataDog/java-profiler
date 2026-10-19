---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 06:50:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (6 unique values: 69-80 cores)</summary>

```
1792406760 80
1792406765 80
1792406770 80
1792406775 80
1792406780 80
1792406785 75
1792406790 75
1792406795 75
1792406800 75
1792406805 73
1792406810 73
1792406815 69
1792406820 69
1792406825 69
1792406830 69
1792406835 69
1792406840 69
1792406845 69
1792406850 69
1792406855 69
```
</details>

---

