---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 09:29:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 9 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 48-59 cores)</summary>

```
1793975072 59
1793975077 59
1793975082 59
1793975087 48
1793975092 48
1793975097 48
1793975102 48
1793975107 48
1793975112 48
1793975117 48
1793975122 48
1793975127 51
1793975132 51
1793975137 51
1793975142 51
1793975147 51
1793975152 51
1793975157 51
1793975162 51
1793975167 51
```
</details>

---

