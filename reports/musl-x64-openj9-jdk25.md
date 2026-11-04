---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 14:11:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 71-78 cores)</summary>

```
1793819179 78
1793819184 78
1793819189 78
1793819194 78
1793819199 78
1793819204 78
1793819209 78
1793819214 78
1793819219 78
1793819224 73
1793819229 73
1793819234 73
1793819239 73
1793819244 73
1793819249 73
1793819254 73
1793819259 73
1793819264 73
1793819269 73
1793819274 73
```
</details>

---

