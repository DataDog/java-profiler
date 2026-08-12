---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 839 |
| Sample Rate | 13.98/sec |
| Health Score | 874% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1786547893 14
1786547898 14
1786547903 14
1786547908 14
1786547913 14
1786547918 14
1786547923 14
1786547928 14
1786547933 14
1786547938 14
1786547943 34
1786547948 34
1786547953 34
1786547958 34
1786547963 34
1786547968 34
1786547973 34
1786547978 34
1786547983 34
1786547988 34
```
</details>

---

