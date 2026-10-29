---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:45:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 85-94 cores)</summary>

```
1793281216 94
1793281221 94
1793281226 94
1793281231 94
1793281236 94
1793281241 94
1793281246 85
1793281251 85
1793281256 85
1793281261 85
1793281266 87
1793281271 87
1793281276 87
1793281281 87
1793281286 87
1793281291 87
1793281296 87
1793281301 87
1793281306 87
1793281311 87
```
</details>

---

