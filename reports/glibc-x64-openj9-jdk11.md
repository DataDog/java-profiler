---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 14:53:13 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 66-82 cores)</summary>

```
1795636150 82
1795636155 82
1795636160 82
1795636165 82
1795636170 82
1795636175 82
1795636180 66
1795636185 66
1795636190 66
1795636195 66
1795636200 66
1795636205 66
1795636210 66
1795636215 66
1795636220 66
1795636225 66
1795636230 66
1795636235 66
1795636240 66
1795636245 66
```
</details>

---

