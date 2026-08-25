---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-25 16:41:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 80-88 cores)</summary>

```
1787690206 88
1787690211 88
1787690216 88
1787690222 88
1787690227 88
1787690232 88
1787690237 88
1787690242 80
1787690247 80
1787690252 80
1787690257 80
1787690262 80
1787690267 80
1787690272 80
1787690277 80
1787690282 80
1787690287 80
1787690292 80
1787690297 80
1787690302 80
```
</details>

---

