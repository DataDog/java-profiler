---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 09:12:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 764 |
| Sample Rate | 12.73/sec |
| Health Score | 796% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (3 unique values: 61-72 cores)</summary>

```
1790687189 72
1790687195 72
1790687200 72
1790687205 72
1790687210 72
1790687215 61
1790687220 61
1790687225 61
1790687230 61
1790687235 61
1790687240 63
1790687245 63
1790687250 63
1790687255 63
1790687260 63
1790687265 63
1790687270 63
1790687275 63
1790687280 63
1790687285 63
```
</details>

---

