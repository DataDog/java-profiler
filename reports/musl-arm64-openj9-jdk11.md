---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 03:56:33 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 35-48 cores)</summary>

```
1792655511 35
1792655516 35
1792655521 35
1792655526 35
1792655532 35
1792655537 35
1792655542 35
1792655547 35
1792655552 35
1792655557 35
1792655562 35
1792655567 35
1792655572 35
1792655577 35
1792655582 35
1792655587 35
1792655592 35
1792655597 35
1792655602 35
1792655607 48
```
</details>

---

