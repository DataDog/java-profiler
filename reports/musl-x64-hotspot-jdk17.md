---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:30:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 55-76 cores)</summary>

```
1795793079 55
1795793084 55
1795793089 55
1795793094 55
1795793099 55
1795793104 55
1795793109 55
1795793114 55
1795793119 55
1795793124 55
1795793129 55
1795793134 55
1795793139 55
1795793144 55
1795793149 74
1795793154 74
1795793159 76
1795793164 76
1795793169 76
1795793174 76
```
</details>

---

