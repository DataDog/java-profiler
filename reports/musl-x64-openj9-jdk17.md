---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 04:39:32 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 67-96 cores)</summary>

```
1790238983 67
1790238988 67
1790238993 67
1790238998 67
1790239003 69
1790239008 69
1790239013 67
1790239018 67
1790239023 67
1790239028 67
1790239033 71
1790239038 71
1790239043 71
1790239048 71
1790239053 71
1790239058 71
1790239063 71
1790239068 73
1790239073 73
1790239078 96
```
</details>

---

