---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 17-48 cores)</summary>

```
1795691114 48
1795691119 48
1795691124 48
1795691129 48
1795691134 48
1795691139 48
1795691144 48
1795691149 48
1795691155 48
1795691160 48
1795691165 48
1795691170 48
1795691175 48
1795691180 48
1795691185 48
1795691190 48
1795691195 48
1795691200 48
1795691205 48
1795691210 48
```
</details>

---

