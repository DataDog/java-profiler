---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-29 00:58:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787979241 64
1787979246 59
1787979251 59
1787979256 59
1787979261 59
1787979266 59
1787979271 59
1787979276 59
1787979281 59
1787979286 59
1787979291 59
1787979296 59
1787979301 59
1787979306 59
1787979311 59
1787979316 59
1787979321 59
1787979326 59
1787979331 59
1787979336 59
```
</details>

---

