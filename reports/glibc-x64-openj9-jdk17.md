---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 10:00:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 428 |

<details>
<summary>CPU Timeline (3 unique values: 68-76 cores)</summary>

```
1790258079 76
1790258084 76
1790258089 76
1790258094 76
1790258099 76
1790258104 76
1790258109 76
1790258114 76
1790258119 76
1790258124 74
1790258129 74
1790258134 74
1790258139 74
1790258144 74
1790258149 74
1790258154 74
1790258159 68
1790258164 68
1790258169 68
1790258174 68
```
</details>

---

