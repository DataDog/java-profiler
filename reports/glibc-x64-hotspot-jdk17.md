---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-01-27 09:00:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 8 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 20.03/sec |
| Health Score | 1252% |
| Threads | 9 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1769514161 32
1769514166 32
1769514171 32
1769514176 32
1769514181 32
1769514186 32
1769514191 22
1769514196 22
1769514201 22
1769514206 22
1769514211 22
1769514216 22
1769514221 22
1769514226 22
1769514231 22
1769514236 22
1769514241 22
1769514246 22
1769514251 22
1769514256 22
```
</details>

---

