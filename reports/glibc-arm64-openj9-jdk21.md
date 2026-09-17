---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 15:59:05 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (4 unique values: 30-48 cores)</summary>

```
1789674894 43
1789674899 43
1789674904 43
1789674909 43
1789674914 43
1789674919 43
1789674924 43
1789674929 48
1789674934 48
1789674939 48
1789674944 48
1789674949 47
1789674954 47
1789674959 47
1789674964 47
1789674969 47
1789674974 47
1789674979 47
1789674984 47
1789674989 47
```
</details>

---

