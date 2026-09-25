---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-25 00:58:48 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790312043 48
1790312048 48
1790312053 48
1790312058 48
1790312064 48
1790312069 48
1790312074 48
1790312079 48
1790312084 48
1790312089 48
1790312094 48
1790312099 48
1790312104 48
1790312109 48
1790312114 48
1790312119 48
1790312124 48
1790312129 48
1790312134 48
1790312139 48
```
</details>

---

