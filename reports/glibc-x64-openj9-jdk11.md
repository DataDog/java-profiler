---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 13:31:16 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (4 unique values: 18-66 cores)</summary>

```
1776274079 18
1776274084 18
1776274089 18
1776274094 18
1776274099 18
1776274104 18
1776274109 18
1776274114 18
1776274119 18
1776274124 25
1776274129 25
1776274134 61
1776274139 61
1776274144 61
1776274149 66
1776274154 66
1776274159 66
1776274164 66
1776274169 66
1776274174 66
```
</details>

---

