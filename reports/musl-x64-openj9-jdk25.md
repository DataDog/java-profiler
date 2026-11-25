---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 4 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1795641260 64
1795641265 64
1795641270 64
1795641275 64
1795641280 62
1795641285 62
1795641290 62
1795641295 62
1795641300 62
1795641305 62
1795641310 62
1795641315 62
1795641320 60
1795641325 60
1795641330 60
1795641335 60
1795641340 60
1795641345 60
1795641350 60
1795641355 60
```
</details>

---

