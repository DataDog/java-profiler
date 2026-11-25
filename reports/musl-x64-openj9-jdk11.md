---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 09:53:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 55-59 cores)</summary>

```
1795618044 55
1795618049 55
1795618054 55
1795618059 55
1795618064 55
1795618069 55
1795618074 55
1795618079 55
1795618084 55
1795618089 55
1795618094 59
1795618099 59
1795618104 59
1795618109 59
1795618114 59
1795618119 59
1795618124 59
1795618129 59
1795618134 59
1795618139 59
```
</details>

---

