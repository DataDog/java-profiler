---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 13:23:22 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787851095 64
1787851100 64
1787851105 64
1787851110 64
1787851115 64
1787851120 64
1787851125 64
1787851130 64
1787851135 64
1787851140 64
1787851145 64
1787851150 64
1787851155 64
1787851160 64
1787851165 64
1787851170 64
1787851175 64
1787851180 64
1787851185 64
1787851190 64
```
</details>

---

