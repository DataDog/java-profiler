---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 05:45:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 9 |
| Allocations | 416 |

<details>
<summary>CPU Timeline (3 unique values: 15-25 cores)</summary>

```
1786527681 25
1786527686 25
1786527691 25
1786527696 25
1786527701 25
1786527706 25
1786527711 25
1786527716 25
1786527721 25
1786527726 25
1786527731 25
1786527736 20
1786527741 20
1786527746 20
1786527751 20
1786527756 20
1786527761 20
1786527766 20
1786527771 20
1786527776 20
```
</details>

---

