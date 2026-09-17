---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 18:02:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 11 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789682120 26
1789682125 26
1789682130 26
1789682135 26
1789682140 26
1789682145 26
1789682150 26
1789682155 26
1789682160 26
1789682165 31
1789682170 31
1789682175 31
1789682180 31
1789682185 31
1789682190 31
1789682195 31
1789682200 31
1789682205 31
1789682210 31
1789682215 31
```
</details>

---

