---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 13:14:49 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790097031 43
1790097036 43
1790097041 43
1790097046 43
1790097051 43
1790097056 43
1790097061 43
1790097066 43
1790097071 48
1790097076 48
1790097081 48
1790097086 48
1790097091 48
1790097096 48
1790097101 48
1790097106 48
1790097111 48
1790097116 48
1790097121 48
1790097126 48
```
</details>

---

