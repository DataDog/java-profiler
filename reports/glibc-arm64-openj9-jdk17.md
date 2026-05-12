---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 05:49:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 13 |
| Allocations | 97 |

<details>
<summary>CPU Timeline (2 unique values: 44-56 cores)</summary>

```
1778579075 56
1778579080 56
1778579085 56
1778579090 56
1778579095 56
1778579100 56
1778579105 56
1778579110 56
1778579115 56
1778579120 56
1778579125 56
1778579130 56
1778579135 56
1778579140 56
1778579145 44
1778579150 44
1778579155 44
1778579160 44
1778579165 44
1778579170 44
```
</details>

---

