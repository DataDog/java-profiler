---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 00:06:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 917 |
| Sample Rate | 15.28/sec |
| Health Score | 955% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1794978129 74
1794978134 74
1794978139 74
1794978144 74
1794978149 76
1794978154 76
1794978159 74
1794978164 74
1794978169 74
1794978174 74
1794978179 74
1794978184 74
1794978189 74
1794978194 74
1794978199 74
1794978204 74
1794978209 74
1794978214 74
1794978219 74
1794978224 76
```
</details>

---

