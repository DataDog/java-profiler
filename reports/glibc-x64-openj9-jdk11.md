---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 19:06:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1792710107 91
1792710112 91
1792710117 91
1792710122 91
1792710127 91
1792710132 91
1792710137 91
1792710142 91
1792710147 91
1792710152 91
1792710157 91
1792710162 91
1792710167 91
1792710172 91
1792710177 91
1792710182 91
1792710187 91
1792710192 93
1792710197 93
1792710202 93
```
</details>

---

