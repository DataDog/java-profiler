---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:40:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 693 |
| Sample Rate | 11.55/sec |
| Health Score | 722% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1789997711 22
1789997716 22
1789997721 22
1789997726 22
1789997731 22
1789997736 22
1789997741 22
1789997746 22
1789997751 22
1789997756 22
1789997761 22
1789997766 20
1789997771 20
1789997776 20
1789997781 20
1789997786 20
1789997791 20
1789997796 20
1789997801 20
1789997806 20
```
</details>

---

