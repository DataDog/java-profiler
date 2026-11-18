---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 14:50:21 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 66-81 cores)</summary>

```
1795031132 66
1795031137 66
1795031142 66
1795031147 66
1795031152 66
1795031157 66
1795031162 68
1795031167 68
1795031172 68
1795031177 68
1795031182 76
1795031187 76
1795031192 76
1795031197 79
1795031202 79
1795031207 79
1795031212 79
1795031217 81
1795031222 81
1795031227 81
```
</details>

---

