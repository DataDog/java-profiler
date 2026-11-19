---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:36:50 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 58-70 cores)</summary>

```
1795113107 68
1795113112 68
1795113117 68
1795113122 68
1795113127 68
1795113132 68
1795113137 68
1795113142 70
1795113147 70
1795113152 70
1795113157 70
1795113162 70
1795113167 70
1795113172 70
1795113177 70
1795113182 70
1795113187 70
1795113192 70
1795113197 70
1795113202 70
```
</details>

---

