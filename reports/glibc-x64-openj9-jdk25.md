---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:18:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 95 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 11 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 13 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 94-96 cores)</summary>

```
1770135185 96
1770135190 96
1770135195 96
1770135200 96
1770135205 96
1770135210 96
1770135215 94
1770135220 94
1770135225 94
1770135230 96
1770135235 96
1770135240 96
1770135245 96
1770135250 96
1770135255 96
1770135260 96
1770135265 96
1770135270 96
1770135275 96
1770135280 96
```
</details>

---

