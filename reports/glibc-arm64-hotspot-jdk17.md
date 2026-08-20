---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 07:52:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1787226457 38
1787226462 38
1787226467 38
1787226472 38
1787226477 38
1787226482 38
1787226487 38
1787226492 38
1787226497 38
1787226502 48
1787226507 48
1787226512 48
1787226517 48
1787226522 48
1787226527 48
1787226532 48
1787226537 48
1787226542 48
1787226547 48
1787226552 48
```
</details>

---

