---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 07:43:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
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
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 13 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1794487222 35
1794487227 40
1794487232 40
1794487237 40
1794487242 40
1794487247 39
1794487252 39
1794487257 39
1794487262 39
1794487267 39
1794487272 39
1794487277 39
1794487282 39
1794487287 39
1794487292 39
1794487297 40
1794487302 40
1794487307 40
1794487312 40
1794487317 40
```
</details>

---

