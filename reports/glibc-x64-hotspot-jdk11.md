---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:46 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 69-72 cores)</summary>

```
1795192094 69
1795192099 69
1795192104 69
1795192109 69
1795192114 69
1795192119 69
1795192124 69
1795192129 69
1795192134 69
1795192139 69
1795192144 69
1795192149 69
1795192154 69
1795192159 69
1795192164 69
1795192169 72
1795192174 72
1795192179 70
1795192184 70
1795192189 70
```
</details>

---

