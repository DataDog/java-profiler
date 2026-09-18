---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:34:13 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 928 |
| Sample Rate | 15.47/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 40-46 cores)</summary>

```
1789719871 46
1789719876 46
1789719881 42
1789719886 42
1789719891 42
1789719896 42
1789719901 42
1789719906 42
1789719911 42
1789719916 40
1789719921 40
1789719926 40
1789719931 40
1789719936 40
1789719941 40
1789719946 42
1789719951 42
1789719956 42
1789719961 42
1789719966 42
```
</details>

---

