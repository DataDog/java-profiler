---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-02 00:58:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 739 |
| Sample Rate | 12.32/sec |
| Health Score | 770% |
| Threads | 11 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1788324831 90
1788324836 90
1788324841 92
1788324846 92
1788324851 92
1788324856 94
1788324861 94
1788324866 92
1788324871 92
1788324876 90
1788324881 90
1788324886 90
1788324891 90
1788324896 88
1788324901 88
1788324906 88
1788324911 88
1788324916 92
1788324921 92
1788324926 92
```
</details>

---

