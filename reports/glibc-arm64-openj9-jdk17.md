---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 08:20:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (5 unique values: 37-47 cores)</summary>

```
1791548029 39
1791548034 39
1791548039 39
1791548044 37
1791548049 37
1791548054 37
1791548059 37
1791548064 37
1791548069 37
1791548074 37
1791548079 40
1791548084 40
1791548089 42
1791548094 42
1791548099 42
1791548104 42
1791548109 42
1791548114 42
1791548119 47
1791548125 47
```
</details>

---

