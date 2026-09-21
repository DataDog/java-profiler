---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 04:44:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 155 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1789979878 48
1789979883 48
1789979888 48
1789979893 48
1789979898 48
1789979903 48
1789979908 48
1789979913 48
1789979918 48
1789979923 48
1789979928 43
1789979933 43
1789979938 43
1789979943 43
1789979948 38
1789979953 38
1789979958 38
1789979963 38
1789979968 38
1789979973 38
```
</details>

---

