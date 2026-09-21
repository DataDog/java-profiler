---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:42:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1789979868 44
1789979873 44
1789979878 44
1789979883 44
1789979888 44
1789979893 44
1789979898 44
1789979903 49
1789979908 49
1789979913 49
1789979918 49
1789979923 49
1789979928 49
1789979933 44
1789979938 44
1789979943 44
1789979948 44
1789979953 44
1789979958 44
1789979963 44
```
</details>

---

