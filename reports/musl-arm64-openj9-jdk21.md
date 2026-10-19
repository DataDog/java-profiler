---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 05:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 36-41 cores)</summary>

```
1792403392 41
1792403397 41
1792403402 41
1792403407 41
1792403412 41
1792403417 41
1792403422 41
1792403427 36
1792403432 36
1792403438 36
1792403443 36
1792403448 36
1792403453 36
1792403458 36
1792403463 36
1792403468 36
1792403473 36
1792403478 36
1792403483 36
1792403488 36
```
</details>

---

