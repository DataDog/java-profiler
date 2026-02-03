---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:54:11 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 10 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1770137395 31
1770137400 31
1770137405 31
1770137410 31
1770137415 32
1770137420 32
1770137425 32
1770137430 32
1770137435 32
1770137440 32
1770137445 27
1770137450 27
1770137455 27
1770137460 27
1770137465 27
1770137470 27
1770137475 27
1770137480 27
1770137485 27
1770137490 27
```
</details>

---

