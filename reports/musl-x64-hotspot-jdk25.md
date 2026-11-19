---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:36:50 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 771 |
| Sample Rate | 12.85/sec |
| Health Score | 803% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 32-53 cores)</summary>

```
1795113110 32
1795113115 32
1795113120 32
1795113125 32
1795113130 32
1795113135 32
1795113140 32
1795113145 32
1795113150 32
1795113155 32
1795113160 32
1795113165 32
1795113170 32
1795113175 32
1795113180 32
1795113185 32
1795113190 32
1795113195 53
1795113200 53
1795113205 53
```
</details>

---

