---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 06:13:35 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 37-48 cores)</summary>

```
1787134019 48
1787134024 48
1787134029 48
1787134034 48
1787134039 48
1787134044 48
1787134049 43
1787134054 43
1787134059 43
1787134064 43
1787134069 43
1787134074 43
1787134079 37
1787134084 37
1787134089 37
1787134094 37
1787134099 37
1787134104 37
1787134109 43
1787134114 43
```
</details>

---

