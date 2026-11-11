---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:22:22 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 59-69 cores)</summary>

```
1794428211 60
1794428216 60
1794428221 69
1794428226 69
1794428231 69
1794428236 69
1794428241 69
1794428246 69
1794428251 69
1794428256 69
1794428261 69
1794428266 69
1794428271 61
1794428276 61
1794428281 61
1794428286 61
1794428291 61
1794428296 61
1794428301 61
1794428306 61
```
</details>

---

