---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:09:23 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 84-89 cores)</summary>

```
1795691114 84
1795691119 84
1795691124 84
1795691129 84
1795691134 84
1795691139 84
1795691144 84
1795691149 87
1795691154 87
1795691159 87
1795691164 87
1795691169 87
1795691174 87
1795691179 87
1795691184 87
1795691189 87
1795691194 87
1795691199 87
1795691204 87
1795691209 87
```
</details>

---

