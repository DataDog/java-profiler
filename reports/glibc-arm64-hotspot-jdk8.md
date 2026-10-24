---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-24 05:55:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 49-56 cores)</summary>

```
1792835475 53
1792835480 53
1792835485 53
1792835490 55
1792835495 55
1792835500 55
1792835505 55
1792835510 56
1792835515 56
1792835520 56
1792835525 56
1792835530 56
1792835535 56
1792835540 56
1792835545 56
1792835550 56
1792835555 56
1792835560 56
1792835565 49
1792835570 49
```
</details>

---

