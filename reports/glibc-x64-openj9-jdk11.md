---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 11:23:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 45-69 cores)</summary>

```
1786547893 45
1786547898 45
1786547903 45
1786547908 45
1786547913 45
1786547918 45
1786547923 47
1786547928 47
1786547933 47
1786547938 47
1786547943 47
1786547948 47
1786547953 47
1786547958 47
1786547963 47
1786547968 47
1786547973 47
1786547978 47
1786547983 69
1786547988 69
```
</details>

---

