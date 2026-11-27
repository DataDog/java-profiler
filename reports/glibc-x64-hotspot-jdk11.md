---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 11:20:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 10 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 75-79 cores)</summary>

```
1795796188 79
1795796193 79
1795796198 79
1795796203 79
1795796208 79
1795796213 79
1795796218 79
1795796223 79
1795796228 79
1795796233 79
1795796238 79
1795796243 79
1795796248 79
1795796253 79
1795796258 79
1795796263 79
1795796268 79
1795796273 79
1795796278 79
1795796283 79
```
</details>

---

