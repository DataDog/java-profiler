---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:05:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793642472 48
1793642477 48
1793642482 48
1793642487 48
1793642492 48
1793642497 48
1793642502 48
1793642507 48
1793642512 48
1793642517 48
1793642522 48
1793642527 48
1793642532 48
1793642537 48
1793642542 48
1793642547 48
1793642552 48
1793642557 48
1793642562 48
1793642567 48
```
</details>

---

