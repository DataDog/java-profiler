---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:15:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795604972 64
1795604977 64
1795604982 64
1795604987 64
1795604992 64
1795604997 64
1795605002 64
1795605007 64
1795605012 64
1795605017 64
1795605022 64
1795605027 64
1795605032 64
1795605037 64
1795605042 64
1795605047 64
1795605052 64
1795605057 64
1795605062 64
1795605067 64
```
</details>

---

