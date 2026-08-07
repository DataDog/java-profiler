---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 05:50:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 10 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 967 |
| Sample Rate | 16.12/sec |
| Health Score | 1007% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1786095977 45
1786095982 45
1786095987 45
1786095992 45
1786095997 45
1786096002 45
1786096007 45
1786096012 45
1786096017 45
1786096022 45
1786096027 43
1786096032 43
1786096037 43
1786096042 43
1786096047 43
1786096052 43
1786096057 43
1786096062 43
1786096067 45
1786096072 45
```
</details>

---

