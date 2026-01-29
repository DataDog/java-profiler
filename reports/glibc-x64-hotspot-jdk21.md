---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 12:19:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 494 |
| Sample Rate | 16.47/sec |
| Health Score | 1029% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 19.80/sec |
| Health Score | 1238% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769706802 32
1769706807 32
1769706812 32
1769706817 32
1769706822 32
1769706827 32
1769706832 32
1769706837 30
1769706842 30
1769706847 30
1769706852 30
1769706857 30
1769706862 30
1769706867 30
1769706872 30
1769706877 30
1769706882 30
1769706887 30
1769706892 30
1769706897 30
```
</details>

---

