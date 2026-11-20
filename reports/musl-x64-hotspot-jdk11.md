---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 13:59:26 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 66-85 cores)</summary>

```
1795200871 84
1795200876 84
1795200881 84
1795200886 82
1795200891 82
1795200896 82
1795200901 82
1795200906 82
1795200911 82
1795200916 82
1795200921 82
1795200926 82
1795200931 82
1795200936 85
1795200941 85
1795200946 85
1795200952 85
1795200957 85
1795200962 85
1795200967 85
```
</details>

---

