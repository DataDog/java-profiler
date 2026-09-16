---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-16 07:29:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 28-33 cores)</summary>

```
1789557876 33
1789557881 33
1789557886 33
1789557891 33
1789557896 33
1789557901 33
1789557906 33
1789557911 33
1789557916 33
1789557921 33
1789557926 33
1789557931 28
1789557936 28
1789557941 28
1789557946 28
1789557951 28
1789557956 28
1789557961 28
1789557966 28
1789557971 28
```
</details>

---

