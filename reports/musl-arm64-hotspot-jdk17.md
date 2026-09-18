---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:28:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1789719926 45
1789719931 45
1789719936 45
1789719941 45
1789719946 45
1789719951 45
1789719956 45
1789719961 45
1789719966 45
1789719971 45
1789719976 45
1789719981 45
1789719986 45
1789719991 45
1789719996 45
1789720001 45
1789720006 45
1789720011 45
1789720016 45
1789720021 45
```
</details>

---

