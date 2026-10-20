---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 14:20:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
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
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 57-61 cores)</summary>

```
1792520059 57
1792520064 57
1792520069 57
1792520074 57
1792520079 57
1792520084 57
1792520089 57
1792520094 57
1792520099 57
1792520104 57
1792520109 57
1792520114 57
1792520119 57
1792520124 59
1792520129 59
1792520134 59
1792520139 59
1792520144 61
1792520149 61
1792520154 61
```
</details>

---

