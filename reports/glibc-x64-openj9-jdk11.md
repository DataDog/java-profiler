---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 07:56:21 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (2 unique values: 64-70 cores)</summary>

```
1786017141 70
1786017146 70
1786017151 70
1786017156 70
1786017161 70
1786017166 70
1786017171 70
1786017176 64
1786017181 64
1786017186 64
1786017191 64
1786017196 64
1786017201 64
1786017206 64
1786017211 64
1786017216 64
1786017221 64
1786017226 64
1786017231 64
1786017236 64
```
</details>

---

