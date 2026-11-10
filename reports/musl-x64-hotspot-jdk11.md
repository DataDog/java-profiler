---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 14:54:03 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1794340091 61
1794340096 61
1794340101 61
1794340106 61
1794340112 61
1794340117 61
1794340122 59
1794340127 59
1794340132 59
1794340137 59
1794340142 59
1794340147 59
1794340152 59
1794340157 59
1794340162 59
1794340167 59
1794340172 59
1794340177 59
1794340182 59
1794340187 59
```
</details>

---

