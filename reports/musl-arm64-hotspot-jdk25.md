---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 40-47 cores)</summary>

```
1793203139 45
1793203144 40
1793203149 40
1793203154 40
1793203159 40
1793203164 40
1793203169 40
1793203174 40
1793203179 40
1793203184 40
1793203189 40
1793203194 45
1793203199 45
1793203204 45
1793203209 43
1793203214 43
1793203219 43
1793203224 43
1793203229 43
1793203234 43
```
</details>

---

