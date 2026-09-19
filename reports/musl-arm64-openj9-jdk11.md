---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-19 00:58:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789793675 32
1789793680 32
1789793685 32
1789793690 32
1789793695 32
1789793700 32
1789793705 32
1789793710 32
1789793715 32
1789793720 32
1789793725 32
1789793730 32
1789793735 32
1789793740 32
1789793745 32
1789793750 32
1789793755 32
1789793760 32
1789793765 32
1789793770 32
```
</details>

---

