---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:56:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 53-74 cores)</summary>

```
1793890198 55
1793890203 55
1793890208 55
1793890213 55
1793890218 55
1793890223 55
1793890228 74
1793890233 74
1793890238 74
1793890243 53
1793890248 53
1793890253 53
1793890258 53
1793890263 53
1793890268 53
1793890273 53
1793890278 53
1793890283 71
1793890288 71
1793890293 71
```
</details>

---

