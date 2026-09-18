---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 04:34:13 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 840 |
| Sample Rate | 14.00/sec |
| Health Score | 875% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 40-42 cores)</summary>

```
1789719900 42
1789719905 42
1789719910 42
1789719915 40
1789719920 40
1789719925 40
1789719930 40
1789719935 40
1789719940 40
1789719945 42
1789719950 42
1789719955 42
1789719961 42
1789719966 42
1789719971 42
1789719976 42
1789719981 42
1789719986 42
1789719991 42
1789719996 42
```
</details>

---

