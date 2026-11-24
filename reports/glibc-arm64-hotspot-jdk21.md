---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 17-29 cores)</summary>

```
1795529700 29
1795529705 29
1795529710 19
1795529715 19
1795529720 19
1795529725 19
1795529730 19
1795529735 19
1795529740 19
1795529745 19
1795529750 19
1795529755 19
1795529760 19
1795529765 19
1795529770 19
1795529775 19
1795529780 19
1795529785 19
1795529790 19
1795529795 19
```
</details>

---

