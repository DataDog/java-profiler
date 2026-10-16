---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:28 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 22-27 cores)</summary>

```
1792139993 22
1792139998 22
1792140003 22
1792140008 22
1792140013 22
1792140018 22
1792140023 22
1792140028 22
1792140033 22
1792140038 27
1792140043 27
1792140048 27
1792140053 27
1792140058 27
1792140063 27
1792140068 27
1792140073 27
1792140078 27
1792140083 27
1792140088 27
```
</details>

---

