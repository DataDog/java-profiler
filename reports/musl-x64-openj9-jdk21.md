---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 07:23:33 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 57-59 cores)</summary>

```
1793359115 57
1793359120 57
1793359125 57
1793359130 59
1793359135 59
1793359140 59
1793359145 59
1793359150 59
1793359155 59
1793359160 59
1793359165 59
1793359170 59
1793359175 59
1793359180 59
1793359185 59
1793359190 59
1793359195 59
1793359200 59
1793359205 59
1793359210 59
```
</details>

---

