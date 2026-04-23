---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 10:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1130 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 72-87 cores)</summary>

```
1776953800 87
1776953805 87
1776953810 87
1776953815 87
1776953820 87
1776953825 87
1776953830 87
1776953835 85
1776953840 85
1776953845 85
1776953850 85
1776953855 85
1776953860 85
1776953865 85
1776953870 85
1776953875 85
1776953880 81
1776953885 81
1776953890 81
1776953895 72
```
</details>

---

