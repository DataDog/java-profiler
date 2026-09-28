---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 00:58:21 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1790571186 96
1790571191 96
1790571196 96
1790571201 96
1790571206 96
1790571211 96
1790571216 96
1790571221 96
1790571226 96
1790571231 96
1790571236 96
1790571241 91
1790571246 91
1790571251 91
1790571256 91
1790571261 91
1790571266 89
1790571271 89
1790571276 89
1790571281 89
```
</details>

---

