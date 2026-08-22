---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 13:05:51 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 28-43 cores)</summary>

```
1787418107 43
1787418112 43
1787418117 38
1787418122 38
1787418127 38
1787418132 38
1787418137 38
1787418142 38
1787418147 33
1787418152 33
1787418157 33
1787418162 33
1787418167 28
1787418172 28
1787418177 28
1787418182 28
1787418187 33
1787418192 33
1787418197 33
1787418202 38
```
</details>

---

