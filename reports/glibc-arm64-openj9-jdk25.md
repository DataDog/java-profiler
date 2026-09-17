---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:03:55 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (2 unique values: 17-48 cores)</summary>

```
1789682191 17
1789682196 17
1789682201 17
1789682206 17
1789682211 17
1789682216 17
1789682221 17
1789682226 17
1789682231 17
1789682236 17
1789682241 17
1789682246 17
1789682251 48
1789682256 48
1789682261 48
1789682266 48
1789682271 48
1789682276 48
1789682281 48
1789682286 48
```
</details>

---

