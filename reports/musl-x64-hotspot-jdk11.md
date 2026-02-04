---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-04 13:27:47 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1770229076 64
1770229081 64
1770229087 62
1770229092 62
1770229097 62
1770229102 62
1770229107 62
1770229112 62
1770229117 59
1770229122 59
1770229127 59
1770229132 59
1770229137 59
1770229142 59
1770229147 59
1770229152 59
1770229157 59
1770229162 59
1770229167 59
1770229172 59
```
</details>

---

