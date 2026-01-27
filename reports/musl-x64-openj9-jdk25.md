---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:00:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 17.17/sec |
| Health Score | 1073% |
| Threads | 10 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 25.63/sec |
| Health Score | 1602% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769514159 30
1769514164 30
1769514169 30
1769514174 30
1769514179 32
1769514184 32
1769514189 32
1769514194 32
1769514199 32
1769514204 32
1769514209 32
1769514214 32
1769514219 32
1769514224 32
1769514229 32
1769514235 32
1769514240 32
1769514245 32
1769514250 32
1769514255 32
```
</details>

---

