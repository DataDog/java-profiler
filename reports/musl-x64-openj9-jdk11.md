---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-24 15:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787600209 94
1787600214 94
1787600219 94
1787600224 94
1787600229 94
1787600234 96
1787600239 96
1787600244 96
1787600250 96
1787600255 96
1787600260 96
1787600265 96
1787600270 96
1787600275 96
1787600280 96
1787600285 96
1787600290 96
1787600295 96
1787600300 96
1787600305 96
```
</details>

---

