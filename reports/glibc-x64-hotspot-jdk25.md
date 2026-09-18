---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:28:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 54-74 cores)</summary>

```
1789719948 54
1789719953 74
1789719958 74
1789719963 74
1789719968 74
1789719973 74
1789719978 74
1789719983 74
1789719988 74
1789719993 74
1789719998 74
1789720003 74
1789720008 74
1789720013 74
1789720018 74
1789720023 74
1789720028 74
1789720033 74
1789720038 74
1789720043 74
```
</details>

---

