---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-16 12:13:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 11 |
| Allocations | 116 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1789574775 48
1789574780 48
1789574785 48
1789574790 48
1789574795 48
1789574800 48
1789574805 48
1789574810 48
1789574815 48
1789574820 48
1789574825 48
1789574830 48
1789574835 48
1789574840 48
1789574845 48
1789574850 44
1789574855 44
1789574860 37
1789574865 37
1789574870 37
```
</details>

---

