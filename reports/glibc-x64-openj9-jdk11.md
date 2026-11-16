---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:41:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 914 |
| Sample Rate | 15.23/sec |
| Health Score | 952% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 48-57 cores)</summary>

```
1794832686 57
1794832691 57
1794832696 57
1794832701 57
1794832706 57
1794832711 57
1794832716 57
1794832721 57
1794832726 57
1794832731 57
1794832736 57
1794832742 57
1794832747 57
1794832752 57
1794832757 57
1794832762 52
1794832767 52
1794832772 54
1794832777 54
1794832782 54
```
</details>

---

