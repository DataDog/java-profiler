---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:23:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 10 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 40-50 cores)</summary>

```
1795108647 40
1795108652 40
1795108657 40
1795108662 40
1795108667 45
1795108672 45
1795108677 45
1795108682 45
1795108687 45
1795108692 45
1795108697 45
1795108702 45
1795108707 50
1795108712 50
1795108717 50
1795108722 50
1795108727 50
1795108732 50
1795108737 50
1795108742 50
```
</details>

---

