---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 08:57:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 54-71 cores)</summary>

```
1793019069 71
1793019074 71
1793019079 71
1793019084 71
1793019089 71
1793019094 71
1793019099 71
1793019104 71
1793019109 71
1793019114 71
1793019119 71
1793019124 69
1793019129 69
1793019134 69
1793019139 69
1793019144 69
1793019149 69
1793019154 69
1793019159 69
1793019164 54
```
</details>

---

