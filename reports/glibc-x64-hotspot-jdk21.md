---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 08:53:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (3 unique values: 20-71 cores)</summary>

```
1792759736 20
1792759741 20
1792759746 20
1792759751 38
1792759756 38
1792759761 38
1792759766 38
1792759771 38
1792759776 71
1792759781 71
1792759786 38
1792759791 38
1792759796 38
1792759801 38
1792759806 38
1792759811 38
1792759816 38
1792759821 38
1792759826 38
1792759831 38
```
</details>

---

