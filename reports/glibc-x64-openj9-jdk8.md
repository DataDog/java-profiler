---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 08:08:21 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 56-61 cores)</summary>

```
1789992201 56
1789992206 56
1789992211 56
1789992216 56
1789992221 56
1789992226 56
1789992231 61
1789992236 61
1789992241 61
1789992246 61
1789992251 61
1789992256 61
1789992261 61
1789992266 61
1789992271 61
1789992276 61
1789992281 61
1789992286 61
1789992291 61
1789992296 61
```
</details>

---

