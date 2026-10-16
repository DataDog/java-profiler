---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 05:53:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1792144124 24
1792144129 27
1792144134 27
1792144139 24
1792144144 24
1792144149 24
1792144154 24
1792144159 24
1792144164 24
1792144169 24
1792144174 24
1792144179 24
1792144184 24
1792144189 24
1792144194 24
1792144199 24
1792144204 24
1792144209 24
1792144214 24
1792144219 24
```
</details>

---

