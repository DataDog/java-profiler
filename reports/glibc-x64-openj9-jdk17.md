---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 17:28:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 930 |
| Sample Rate | 15.50/sec |
| Health Score | 969% |
| Threads | 11 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (4 unique values: 54-80 cores)</summary>

```
1789680226 54
1789680231 54
1789680236 54
1789680241 63
1789680246 63
1789680251 63
1789680256 55
1789680262 55
1789680267 55
1789680272 55
1789680277 55
1789680282 55
1789680287 55
1789680292 55
1789680297 55
1789680302 55
1789680307 55
1789680312 55
1789680317 80
1789680322 80
```
</details>

---

