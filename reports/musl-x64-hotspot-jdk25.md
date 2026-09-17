---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:00:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (4 unique values: 69-79 cores)</summary>

```
1789682070 69
1789682075 69
1789682080 69
1789682085 69
1789682090 69
1789682095 69
1789682100 69
1789682105 71
1789682110 71
1789682115 73
1789682120 73
1789682125 73
1789682130 73
1789682135 73
1789682140 71
1789682145 71
1789682150 71
1789682155 71
1789682160 71
1789682165 71
```
</details>

---

