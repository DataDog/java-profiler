---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:09:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1795691124 48
1795691129 48
1795691134 48
1795691139 48
1795691144 48
1795691149 48
1795691154 48
1795691159 48
1795691164 48
1795691169 48
1795691174 48
1795691179 48
1795691184 48
1795691189 48
1795691194 48
1795691199 48
1795691204 48
1795691209 48
1795691214 48
1795691219 48
```
</details>

---

