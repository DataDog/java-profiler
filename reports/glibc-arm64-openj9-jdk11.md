---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:23:33 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795195161 64
1795195166 64
1795195171 64
1795195176 64
1795195181 64
1795195186 64
1795195191 64
1795195196 64
1795195201 64
1795195206 64
1795195211 64
1795195216 64
1795195221 59
1795195226 59
1795195231 59
1795195236 59
1795195241 59
1795195246 59
1795195251 59
1795195256 59
```
</details>

---

