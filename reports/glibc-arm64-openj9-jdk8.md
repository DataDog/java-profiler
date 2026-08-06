---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-06 08:59:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 17-24 cores)</summary>

```
1786020952 17
1786020957 17
1786020962 17
1786020967 17
1786020972 20
1786020977 20
1786020982 22
1786020987 22
1786020992 22
1786020997 22
1786021002 22
1786021007 22
1786021012 22
1786021017 22
1786021022 22
1786021027 22
1786021032 22
1786021037 22
1786021042 22
1786021047 22
```
</details>

---

