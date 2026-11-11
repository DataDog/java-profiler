---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 06:07:53 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 48-73 cores)</summary>

```
1794394990 50
1794394995 50
1794395000 50
1794395005 48
1794395010 48
1794395015 73
1794395020 73
1794395025 73
1794395030 73
1794395035 73
1794395040 73
1794395045 73
1794395050 73
1794395055 73
1794395060 73
1794395065 73
1794395070 73
1794395075 73
1794395080 73
1794395085 73
```
</details>

---

