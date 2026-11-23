---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:36:29 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 39 |
| Sample Rate | 0.65/sec |
| Health Score | 41% |
| Threads | 11 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 18-34 cores)</summary>

```
1795455099 18
1795455104 18
1795455109 18
1795455114 18
1795455119 18
1795455124 18
1795455129 18
1795455134 18
1795455139 18
1795455144 18
1795455149 18
1795455154 34
1795455159 34
1795455164 34
1795455169 34
1795455174 34
1795455179 34
1795455184 34
1795455189 34
1795455194 34
```
</details>

---

