---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 10:56:46 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 288 |
| Sample Rate | 4.80/sec |
| Health Score | 300% |
| Threads | 9 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792767134 64
1792767139 64
1792767144 64
1792767149 64
1792767154 64
1792767159 51
1792767164 51
1792767169 51
1792767174 51
1792767179 51
1792767184 51
1792767189 51
1792767194 51
1792767199 51
1792767204 51
1792767209 51
1792767214 51
1792767219 51
1792767224 51
1792767229 51
```
</details>

---

