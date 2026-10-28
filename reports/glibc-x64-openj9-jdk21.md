---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 07:48:55 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 10 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 45-51 cores)</summary>

```
1793187893 45
1793187898 45
1793187903 45
1793187908 45
1793187913 45
1793187918 45
1793187923 45
1793187928 45
1793187933 45
1793187938 45
1793187943 45
1793187948 45
1793187953 45
1793187958 45
1793187963 45
1793187968 45
1793187973 45
1793187978 51
1793187983 51
1793187988 51
```
</details>

---

