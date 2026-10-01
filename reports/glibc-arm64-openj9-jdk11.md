---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-01 07:40:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 12 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1790854512 39
1790854517 39
1790854522 39
1790854527 39
1790854532 39
1790854537 39
1790854542 39
1790854547 34
1790854552 34
1790854557 34
1790854562 34
1790854567 34
1790854572 34
1790854577 34
1790854582 34
1790854587 34
1790854592 34
1790854597 34
1790854602 39
1790854607 39
```
</details>

---

