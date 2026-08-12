---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 11:23:58 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 32-40 cores)</summary>

```
1786547892 32
1786547897 32
1786547902 32
1786547907 32
1786547913 32
1786547918 32
1786547923 32
1786547928 32
1786547933 32
1786547938 32
1786547943 32
1786547948 32
1786547953 32
1786547958 32
1786547963 32
1786547968 32
1786547973 32
1786547978 32
1786547983 32
1786547988 32
```
</details>

---

