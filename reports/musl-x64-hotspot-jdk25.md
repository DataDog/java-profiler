---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:32:32 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 969 |
| Sample Rate | 16.15/sec |
| Health Score | 1009% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795094953 87
1795094958 87
1795094963 87
1795094968 87
1795094973 87
1795094978 87
1795094983 87
1795094988 87
1795094993 87
1795094998 87
1795095003 87
1795095008 87
1795095013 87
1795095018 87
1795095023 87
1795095028 96
1795095033 96
1795095038 96
1795095043 96
1795095048 96
```
</details>

---

