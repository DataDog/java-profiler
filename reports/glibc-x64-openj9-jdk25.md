---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 10:11:27 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1786457196 94
1786457201 94
1786457206 94
1786457211 94
1786457216 94
1786457221 94
1786457226 94
1786457231 94
1786457236 94
1786457241 92
1786457246 92
1786457251 92
1786457256 92
1786457261 92
1786457266 92
1786457271 92
1786457276 96
1786457281 96
1786457286 96
1786457291 96
```
</details>

---

