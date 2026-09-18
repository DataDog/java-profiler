---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 04:28:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 12 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 84-96 cores)</summary>

```
1789719911 84
1789719916 86
1789719921 86
1789719926 86
1789719931 86
1789719936 86
1789719941 86
1789719946 86
1789719951 86
1789719956 86
1789719961 86
1789719966 96
1789719971 96
1789719976 96
1789719981 96
1789719986 96
1789719991 96
1789719996 96
1789720001 96
1789720006 96
```
</details>

---

