---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-15 05:47:16 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 38-58 cores)</summary>

```
1786786948 58
1786786953 58
1786786958 58
1786786963 58
1786786968 58
1786786973 58
1786786978 58
1786786983 58
1786786988 58
1786786993 58
1786786998 58
1786787003 58
1786787008 38
1786787013 38
1786787018 38
1786787023 38
1786787028 38
1786787033 38
1786787038 38
1786787043 38
```
</details>

---

