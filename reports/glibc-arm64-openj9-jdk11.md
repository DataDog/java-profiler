---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 10:08:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1787321021 40
1787321026 40
1787321031 40
1787321036 40
1787321041 40
1787321046 40
1787321051 40
1787321056 40
1787321061 40
1787321066 40
1787321071 40
1787321076 35
1787321081 35
1787321086 35
1787321091 35
1787321096 35
1787321101 35
1787321106 35
1787321111 35
1787321116 35
```
</details>

---

