---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:21:29 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 44-53 cores)</summary>

```
1795706160 46
1795706165 46
1795706170 46
1795706175 46
1795706180 46
1795706185 44
1795706190 44
1795706195 44
1795706200 44
1795706205 44
1795706210 44
1795706215 44
1795706220 44
1795706225 44
1795706230 44
1795706235 44
1795706240 44
1795706245 44
1795706250 44
1795706255 44
```
</details>

---

