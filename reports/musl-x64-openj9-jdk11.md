---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 12:35:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1090 |
| Sample Rate | 18.17/sec |
| Health Score | 1136% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1790181053 79
1790181058 79
1790181063 81
1790181068 81
1790181074 81
1790181079 81
1790181084 81
1790181089 81
1790181094 81
1790181099 81
1790181104 81
1790181109 79
1790181114 79
1790181119 79
1790181124 79
1790181129 79
1790181134 79
1790181139 79
1790181144 79
1790181149 79
```
</details>

---

