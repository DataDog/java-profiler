---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 07:47:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 32-44 cores)</summary>

```
1794487362 36
1794487367 36
1794487372 36
1794487377 36
1794487382 36
1794487387 36
1794487392 36
1794487397 36
1794487402 36
1794487407 36
1794487412 36
1794487417 36
1794487422 32
1794487427 32
1794487432 32
1794487437 32
1794487442 32
1794487447 32
1794487452 32
1794487457 32
```
</details>

---

