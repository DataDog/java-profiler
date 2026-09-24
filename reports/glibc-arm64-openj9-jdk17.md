---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-24 05:51:59 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 35-39 cores)</summary>

```
1790243083 39
1790243088 39
1790243093 39
1790243098 39
1790243103 39
1790243108 39
1790243113 39
1790243118 39
1790243123 39
1790243128 39
1790243133 38
1790243138 38
1790243143 38
1790243148 38
1790243153 37
1790243158 37
1790243163 35
1790243168 35
1790243173 35
1790243178 35
```
</details>

---

