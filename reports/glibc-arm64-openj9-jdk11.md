---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 12:21:54 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 48-64 cores)</summary>

```
1795540621 48
1795540626 48
1795540631 48
1795540636 64
1795540641 64
1795540646 64
1795540651 64
1795540656 64
1795540661 64
1795540666 64
1795540671 64
1795540676 64
1795540681 64
1795540686 64
1795540691 64
1795540696 64
1795540701 64
1795540706 64
1795540711 64
1795540716 64
```
</details>

---

