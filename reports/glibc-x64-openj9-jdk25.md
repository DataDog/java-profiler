---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 371 |
| Sample Rate | 6.18/sec |
| Health Score | 386% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 55-76 cores)</summary>

```
1792139999 55
1792140004 55
1792140009 55
1792140014 55
1792140019 55
1792140024 55
1792140029 55
1792140034 55
1792140039 55
1792140044 55
1792140049 55
1792140054 76
1792140059 76
1792140064 59
1792140069 59
1792140074 59
1792140079 59
1792140084 59
1792140089 59
1792140094 59
```
</details>

---

