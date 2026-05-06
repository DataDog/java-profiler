---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-06 14:42:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 962 |
| Sample Rate | 16.03/sec |
| Health Score | 1002% |
| Threads | 12 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1778092681 85
1778092686 85
1778092691 85
1778092696 87
1778092701 87
1778092706 83
1778092711 83
1778092716 83
1778092721 83
1778092726 83
1778092731 83
1778092736 83
1778092741 83
1778092746 83
1778092751 83
1778092756 83
1778092761 83
1778092766 83
1778092771 83
1778092776 83
```
</details>

---

