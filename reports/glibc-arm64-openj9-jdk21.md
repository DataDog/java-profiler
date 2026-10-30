---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 17:09:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 168 |
| Sample Rate | 2.80/sec |
| Health Score | 175% |
| Threads | 11 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1793394276 44
1793394281 44
1793394286 44
1793394291 44
1793394296 44
1793394301 44
1793394306 46
1793394311 46
1793394316 46
1793394321 46
1793394326 46
1793394331 46
1793394336 48
1793394341 48
1793394346 48
1793394351 48
1793394356 46
1793394361 46
1793394366 46
1793394371 46
```
</details>

---

