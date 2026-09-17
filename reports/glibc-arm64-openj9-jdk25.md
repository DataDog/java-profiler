---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 10:30:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 31-34 cores)</summary>

```
1789655049 31
1789655054 31
1789655059 31
1789655064 31
1789655069 31
1789655074 31
1789655079 31
1789655084 31
1789655089 31
1789655095 31
1789655100 31
1789655105 31
1789655110 31
1789655115 33
1789655120 33
1789655125 33
1789655130 33
1789655135 31
1789655140 31
1789655145 31
```
</details>

---

