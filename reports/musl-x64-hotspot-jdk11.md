---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 18:19:18 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (3 unique values: 44-63 cores)</summary>

```
1792448068 44
1792448073 44
1792448078 44
1792448083 44
1792448088 61
1792448093 61
1792448098 61
1792448103 61
1792448108 61
1792448113 61
1792448118 61
1792448123 61
1792448128 61
1792448133 61
1792448138 61
1792448143 61
1792448148 63
1792448153 63
1792448158 63
1792448163 63
```
</details>

---

