---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-06 09:29:15 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 205 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1793975112 51
1793975117 51
1793975122 51
1793975127 51
1793975132 51
1793975137 51
1793975142 51
1793975147 51
1793975152 64
1793975157 64
1793975162 64
1793975167 64
1793975172 64
1793975177 64
1793975182 64
1793975187 64
1793975192 64
1793975197 64
1793975202 64
1793975207 64
```
</details>

---

